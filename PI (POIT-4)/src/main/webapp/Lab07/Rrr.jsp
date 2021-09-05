<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ page import="lab06.helpers.CBean"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Rrr.jsp</title>
</head>
<body>
	<h1 align="center">Request Scope</h1>
	<c:if test="${requestScope.CBean != null}">
		<h3>CBean Value 1: ${requestScope.CBean.getValue1()}</h3>
		<h3>CBean Value 2: ${requestScope.CBean.getValue2()}</h3>
		<h3>CBean Value 3: ${requestScope.CBean.getValue3()}</h3>
	</c:if>
	<c:if test="${requestScope.CBean == null}">
		<h3>CBean Value is NULL!</h3>
	</c:if>
</body>
</html>