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
	<%! int hour = LocalTime.now().getHour();
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
		<jsp:forward page="night.jsp" />
	<%} else if (hour >= 6 && hour <= 11) {%>
		<jsp:forward page="morning.jsp" />
	<%} else if (hour >= 12 && hour <= 17) {%>
		<jsp:forward page="afternoon.jsp" />
	<%} else {%>
		<jsp:forward page="evening.jsp" />
	<%}%>
</body>
</html>