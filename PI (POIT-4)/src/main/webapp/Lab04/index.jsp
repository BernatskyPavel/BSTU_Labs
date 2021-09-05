<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ page import="java.time.LocalTime"%>
<%@ page import="java.time.LocalDate"%>
<%@ page import="java.time.format.TextStyle"%>
<%@ page import="java.util.Locale"%>
<%@ taglib prefix="f" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt"%>
<%@ taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<html>
<head>
<title>Index.jsp</title>
</head>
<style>
	th, td{
		border-color: black;
	    border-width: 1px;
	    border-style: solid;
	}
</style>
<body>
	<%!int hour = LocalTime.now().getHour();
	private LocalDate[] getArrayOfDates() {
		LocalDate[] result = new LocalDate[7];
		LocalDate current = LocalDate.now();
		for (int i = 0; i < 7; i++) {
			result[i] = current.plusDays(i);
		}
		return result;
	}
	%>
	<%LocalDate[] dates = getArrayOfDates();
	  request.setAttribute("dates", dates);%>
	<%if (hour >= 0 && hour <= 5) {%>
	<h3>Good Night!</h3>
	<%} else if (hour >= 6 && hour <= 11) {%>
	<h3>Good Morning!</h3>
	<%} else if (hour >= 12 && hour <= 17) {%>
	<h3>Good Afternoon!</h3>
	<%} else {%>
	<h3>Good Evening!</h3>
	<%}%>
	<table style="border:1px solid black; border-collapse:collapse;">
		<tr>
			<th>Дата</th>
			<th>День недели</th>
		</tr>
		<c:forEach var="date" items="${dates}">
		<tr>
			<td>${date.toString()}</td>
			<td>${date.getDayOfWeek().getDisplayName(TextStyle.FULL, Locale.forLanguageTag("ru"))}</td>
		</tr>	
		</c:forEach>
	</table>
	<br/>
	<div id="press-div" style="display: none;">
		<%if (hour >= 0 && hour <= 5) {%>
		<%@include file="night.jsp" %>
		<%} else if (hour >= 6 && hour <= 11) {%>
		<%@include file="morning.jsp" %>
		<%} else if (hour >= 12 && hour <= 17) {%>
		<%@include file="afternoon.jsp" %>
		<%} else {%>
		<%@include file="evening.jsp" %>
		<%}%>
	</div>
	<button onclick="onPress('press-div')">Press Directive</button>
	<br/>
	<div id="press-div-jsp" style="display: none;">
		<%if (hour >= 0 && hour <= 5) {%>
		<jsp:include page="night.jsp" />
		<%} else if (hour >= 6 && hour <= 11) {%>
		<jsp:include page="morning.jsp" />
		<%} else if (hour >= 12 && hour <= 17) {%>
		<jsp:include page="afternoon.jsp" />
		<%} else {%>
		<jsp:include page="evening.jsp" />
		<%}%>
	</div>
	<button onclick="onPress('press-div-jsp')">Press JSP</button>
	<br/>
	<div id="press-div-servlet" style="display: none;">
		<jsp:include page="/Lab04/GoAfternoon"></jsp:include>
	</div>
	<button onclick="onPress('press-div-servlet')">Press Servlet</button>
	<br/>
	<iframe id="press-div-forward" src="./forward.jsp" width="640" height="480" id="press-div-jsp" style="display: none;"> 
	</iframe>
	<button onclick="onPress('press-div-forward')">Press Forward</button>
	<br/>
	<form action="./GoJjj" method="get">
		<input type="radio" name="type" value="simple"/>Simple<br/>
		<input type="radio" name="type" value="get"/>In-box Get Request<br/>
		<input type="radio" name="type" value="post"/>In-box Post Request<br/>
		<input type="submit" value="Submit"/>
	</form>
	<script type="text/javascript">
		function onPress(id){
			document.getElementById(id).style.display = "block";
		}
	</script>
</body>
</html>