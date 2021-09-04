<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib prefix="bpv" uri="./Lab05/bpvtags.tld"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Ttt.jsp</title>
</head>
<body>
	<bpv:Dossier action="./GoTtt">
		<bpv:Surname />
		<bpv:Lastname />
		<bpv:Sex />
		<bpv:Submit />
	</bpv:Dossier>
</body>
</html>