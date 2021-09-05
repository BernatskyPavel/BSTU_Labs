package lab16.servlets;

import java.io.IOException;

import jakarta.websocket.OnClose;
import jakarta.websocket.OnError;
import jakarta.websocket.OnMessage;
import jakarta.websocket.OnOpen;
import jakarta.websocket.Session;
import jakarta.websocket.server.ServerEndpoint;

@ServerEndpoint(value = "/Lab16/socket")
public class Socket {
	public Socket() {
		System.out.println("class loaded " + this.getClass());
	}

	@OnOpen
	public void onOpen(Session session) {
		System.out.printf("Session opened, id: %s%n", session.getId());
		try {
			session.getBasicRemote().sendText("Hi there, we are successfully connected.");
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}

	@OnMessage
	public void onMessage(String message, Session session) {
		System.out.printf("Message received. Session id: %s Message: %s%n", session.getId(), message);
		try {
			session.getBasicRemote().sendText(String.format("We received your message: %s%n", message));
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}

	@OnError
	public void onError(Throwable e) {
		e.printStackTrace();
	}

	@OnClose
	public void onClose(Session session) {
		System.out.printf("Session closed with id: %s%n", session.getId());
	}
}
