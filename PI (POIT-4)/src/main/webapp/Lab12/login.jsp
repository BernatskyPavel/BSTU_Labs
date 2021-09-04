<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Login.jsp</title>
</head>
<body>
	<h3>Login Form</h3>
	<br />
	<form method="post" action="j_security_check">
		Username: <input type="text" name="j_username" /><br /> 
		Password: <input type="text" name="j_password" /><br /> 
		<input type="submit" />
	</form>
</body>
</html>