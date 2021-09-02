<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Error.aspx.cs" Inherits="Lab_03.ErrorPages.WebForm1" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <%=Page.Request.HttpMethod + Page.Request.Url + "- не поддерживается!"%>
        </div>
    </form>
</body>
</html>
