<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Index.jsp</title>
</head>
<body>
	<form method="post" name="lab09-form" action="./GoCcc">
		Value1: <input type="text" name="Value1"/><br/>
		Value2: <input type="text" name="Value2"/><br/>
		Value3: <input type="text" name="Value3"/><br/>
		CBean: <input type="radio" name="CBean" value="new"/>New <input type="radio" name="CBean" value="old"/>Old <br/>
		<input type="submit" value="submit" name="button"/>
	</form>
</body>
</html>