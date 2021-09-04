<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ page import="jakarta.mail.Session"%>
<%@ page import="jakarta.mail.Store"%>
<%@ page import="jakarta.mail.Folder"%>
<%@ page import="jakarta.mail.Message"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Index.jsp</title>
</head>
<body>
	<%
		Folder folder = (Folder)application.getAttribute("folder");
	    folder.open(Folder.READ_ONLY);
		Message[] msgs = folder.getMessages();
		int count = folder.getMessageCount();
		for (int i = 0; i < count; i++) {
			Message msg = msgs[i];
	%>
	<p id="msg<%=i%>"><%=msg.getSubject()%></p>
	<%
		}
	%>
</body>
</html>