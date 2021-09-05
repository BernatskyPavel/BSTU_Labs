<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ page import="lab06.helpers.CBean"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Ccc.jsp</title>
</head>
<body>
	<h1 align="center">Application Scope</h1>
	<h3>CBean Value 1: ${applicationScope.CBean.getValue1()}</h3>
	<h3>CBean Value 2: ${applicationScope.CBean.getValue2()}</h3>
	<h3>CBean Value 3: ${applicationScope.CBean.getValue3()}</h3>
</body>
</html>