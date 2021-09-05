package lab10.servlets;

import java.io.File;
import java.io.IOException;
import java.security.NoSuchAlgorithmException;
import java.security.Provider;
import java.security.Security;
import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Types;
import java.util.HashMap;
import java.util.Map;

import org.wildfly.security.auth.server.IdentityCredentials;
import org.wildfly.security.credential.PasswordCredential;
import org.wildfly.security.credential.store.CredentialStore;
import org.wildfly.security.credential.store.CredentialStore.CredentialSourceProtectionParameter;
import org.wildfly.security.credential.store.CredentialStore.ProtectionParameter;
import org.wildfly.security.credential.store.CredentialStoreException;
import org.wildfly.security.credential.store.UnsupportedCredentialTypeException;
import org.wildfly.security.credential.store.WildFlyElytronCredentialStoreProvider;
import org.wildfly.security.password.Password;
import org.wildfly.security.password.WildFlyElytronPasswordProvider;
import org.wildfly.security.password.interfaces.ClearPassword;

import jakarta.servlet.ServletConfig;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lab02.servlets.Sss;


public class DBServlet extends Sss {

	/**
	 * 
	 */
	private static final long serialVersionUID = -8200959721628244714L;
	private static final String DB_URL = "jdbc:postgresql://127.0.0.1:5432/Java10";
	private static final String USER = "postgres";
	private static String PASS = "";
	private static final Provider CREDENTIAL_STORE_PROVIDER = new WildFlyElytronCredentialStoreProvider();
    private static final Provider PASSWORD_PROVIDER = new WildFlyElytronPasswordProvider();
	private static Connection connection;
	
	static {
        Security.addProvider(PASSWORD_PROVIDER);
	}

	@Override
	public void init(ServletConfig config) throws ServletException {
		super.init(config);
		print(":init");
		
		Password storePassword = ClearPassword.createRaw(ClearPassword.ALGORITHM_CLEAR, "qwerty".toCharArray());
		ProtectionParameter protectionParameter = new CredentialSourceProtectionParameter(IdentityCredentials.NONE.withCredential(new PasswordCredential(storePassword)));
		
		try {
			Class.forName("org.postgresql.Driver");
			CredentialStore credentialStore = CredentialStore.getInstance("KeyStoreCredentialStore", CREDENTIAL_STORE_PROVIDER);
			Map<String, String> configuration = new HashMap<>();
			String configPath = System.getProperty("jboss.server.config.dir");
			configuration.put("keyStoreType", "JCEKS");
			configuration.put("location", configPath+File.separator+"databasecreds.cs");
			credentialStore.initialize(configuration, protectionParameter);
			ClearPassword password = (ClearPassword) credentialStore.retrieve("lab10dbpass", PasswordCredential.class).getPassword();
			PASS = new String(password.getPassword());
			connection = DriverManager.getConnection(DB_URL, USER, PASS);
		} catch (ClassNotFoundException e) {
			System.out.println("PostgreSQL JDBC Driver is not found. Include it in your library path ");
		} catch (SQLException e) {
			System.out.println("Connection Failed");
		} catch (NoSuchAlgorithmException e) {
			System.out.println("Algorithm is not found!");
		} catch (UnsupportedCredentialTypeException e) {
			System.out.println("Credential Type is not supported!");
		} catch (CredentialStoreException e) {
			System.out.println("Credential Store is not working! Error: "+e.getMessage());
			
		}
	}

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		super.print(":doGet");
		resp.getWriter().write("Error: Method is not available!");
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		super.print(":doPost");
		String type = req.getParameter("type");
		if (connection != null) {
			String param = "";
			String response = "";
			switch (type.toLowerCase()) {
			case "static":
				Statement statement;
				try {
					statement = connection.createStatement();
					ResultSet result = statement.executeQuery("select * from public.\"Example\";");
					response += "-----Static Statement-----\n";
					while (result.next()) {
						response = response + result.getInt(1) + " - " + result.getString(2) + " - " + result.getInt(3)
								+ "\n";
					}
					resp.getWriter().write(response);
					return;
				} catch (SQLException e) {
					System.out.println(e.getMessage());
					resp.getWriter().write(" Statement Failed");
				}
				break;
			case "dynamic":

				try {
					param = req.getParameter("dp");
					PreparedStatement pstatement = connection
							.prepareStatement("select * from public.\"Example\" where text like ?;");
					pstatement.setString(1, param + "%");
					ResultSet result = pstatement.executeQuery();
					response += "-----Prepared Statement-----\n";
					while (result.next()) {
						response = response + result.getInt(1) + " - " + result.getString(2) + " - " + result.getInt(3)
								+ "\n";
					}
					resp.getWriter().write(response);
					return;
				} catch (SQLException e) {
					System.out.println(e.getMessage());
					resp.getWriter().write("Prepared Statement Failed");
				}
				break;
			case "proc":
				try {
					param = req.getParameter("dp");
					CallableStatement proc = connection.prepareCall("{?=call example_func(?)}");
					proc.registerOutParameter(1, Types.BIGINT);
					proc.setString(2, param);
					response += "-----Callable Statement-----\n";
					proc.execute();
					response = response + "Result:" + proc.getLong(1);
					resp.getWriter().write(response);
					return;
				} catch (SQLException e) {
					System.out.println(e.getMessage());
					resp.getWriter().write("Callable Statement Failed");
				}
				break;
			default:
				break;
			}

		} else {
			resp.getWriter().write("Failed to make connection to database");
			System.out.println("Failed to make connection to database");
		}
	}

	@Override
	public void destroy() {
		super.destroy();
		print(":destroy");
		try {
			if (!connection.isClosed())
				connection.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

}
