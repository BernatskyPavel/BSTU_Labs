<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Index.jsp</title>
</head>
<body>
	<form method="post" name="lab10-form" action="./GoDb">
		Type: <input type="radio" name="type" value="static" checked />Static
		<input type="radio" name="type" value="dynamic" />Dynamic
		<input type="radio" name="type" value="proc" />Procedure<br/>
		Dynamic/procedure param: <input type="text" name="dp"/><br/>
		<input type="submit" value="submit" name="button" />
	</form>
</body>
</html>