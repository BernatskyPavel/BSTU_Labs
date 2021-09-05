<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Index.jsp</title>
</head>
<body>
	<h1>Request Scope</h1>
	<form method="post" name="lab07-request-form" action="./GoRrr">
		Value1: <input type="text" name="Value1"/><br/>
		Value2: <input type="text" name="Value2"/><br/>
		Value3: <input type="text" name="Value3"/><br/>
		CBean: <input type="radio" name="CBean" value="new"/>New <input type="radio" name="CBean" value="old"/>Old <br/>
		<input type="submit" value="submit" name="button"/>
	</form>
	<br/>
	<h1>Session Scope</h1>
	<form method="post" name="lab07-session-form" action="./GoSss">
		Value1: <input type="text" name="Value1"/><br/>
		Value2: <input type="text" name="Value2"/><br/>
		Value3: <input type="text" name="Value3"/><br/>
		CBean: <input type="radio" name="CBean" value="new"/>New <input type="radio" name="CBean" value="old"/>Old <br/>
		<input type="submit" value="submit" name="button"/>
	</form>
</body>
</html>