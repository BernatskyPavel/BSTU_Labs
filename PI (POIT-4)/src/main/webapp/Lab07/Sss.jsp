<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ page import="lab06.helpers.CBean"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Sss.jsp</title>
</head>
<body>
	<h1 align="center">Session Scope</h1>
	<c:if test="${sessionScope.CBean != null}">
		<h3>CBean Value 1: ${sessionScope.CBean.getValue1()}</h3>
		<h3>CBean Value 2: ${sessionScope.CBean.getValue2()}</h3>
		<h3>CBean Value 3: ${sessionScope.CBean.getValue3()}</h3>
	</c:if>
	<c:if test="${sessionScope.CBean == null}">
		<h3>CBean Value is NULL!</h3>
	</c:if>
</body>
</html>