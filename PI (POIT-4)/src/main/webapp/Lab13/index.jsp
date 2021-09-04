<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ page import="lab13.helpers.DocFilter" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Index.jsp</title>
</head>
<body>
	<%
		String dir = application.getInitParameter("Lab13Files");
		DocFilter filter = new DocFilter(dir, "doc");
		String file = null;
		String[] list = filter.getFilelist();
		for(int i=0; i<list.length;i++){
			file = list[i];	
	%>
	<br/>
	<a href="./GoSss?file=<%=file%>"><%=file%></a>
	<%}%>
</body>
</html>