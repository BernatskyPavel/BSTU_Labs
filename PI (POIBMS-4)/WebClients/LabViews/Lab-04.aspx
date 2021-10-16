<%@ Page Title="Lab-04" Language="C#" MasterPageFile="~/Site.Master" Theme="Lab-04" AutoEventWireup="true" CodeBehind="Lab-04.aspx.cs" Inherits="WebClients.LabViews.Lab_04" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <h2><%: Title %>.</h2>
    <style>
        input {
            margin-right: 10px;
            margin-left: 10px;
        }

        label {
            margin-bottom: 10px;
            margin-top: 10px;
        }
    </style>
    <asp:Table runat="server" BorderStyle="None" Width="650px">
        <asp:TableRow>
            <asp:TableCell HorizontalAlign="Center" ColumnSpan="4">
                <label>Method Add</label>
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell ColumnSpan="4" HorizontalAlign="Center">
                <asp:TextBox ID="add_1" runat="server" ToolTip="Integer" /><b>+</b>
                <asp:TextBox ID="add_2" runat="server" ToolTip="Integer" />
                <asp:Button ID="add_btn" runat="server" Text="=" OnClick="add_btn_Click"/>
                <asp:TextBox ID="add_r" runat="server" ReadOnly="true" />
            </asp:TableCell>
        </asp:TableRow>
    </asp:Table>
    <asp:Table runat="server" BorderStyle="None" Width="650px">
        <asp:TableRow>
            <asp:TableCell HorizontalAlign="Center" ColumnSpan="4">
                <label>Method Concat</label>
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell ColumnSpan="4" HorizontalAlign="Center">
                <asp:TextBox ID="concat_1" runat="server" ToolTip="String" /><b>+</b>
                <asp:TextBox ID="concat_2" runat="server" ToolTip="Double" />
                <asp:Button ID="concat_btn" runat="server" Text="=" OnClick="concat_btn_Click" />
                <asp:TextBox ID="concat_r" runat="server" ReadOnly="true" />
            </asp:TableCell>
        </asp:TableRow>
    </asp:Table>
    <asp:Table runat="server" BorderStyle="None" Width="650px">
        <asp:TableRow>
            <asp:TableCell HorizontalAlign="Center" ColumnSpan="5">
                <label>Method Sum</label>
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell HorizontalAlign="Center">
                Struct A1
            </asp:TableCell>
            <asp:TableCell></asp:TableCell>
            <asp:TableCell HorizontalAlign="Center">
                Struct A2
            </asp:TableCell>
            <asp:TableCell></asp:TableCell>
            <asp:TableCell HorizontalAlign="Center">
                Result Struct
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell>
                S:
                <asp:TextBox ID="a1_S" runat="server" ToolTip="String"/>
            </asp:TableCell>
            <asp:TableCell RowSpan="3" HorizontalAlign="Center" Width="10%">
                <b>+</b>
            </asp:TableCell>
            <asp:TableCell>
                S:
                <asp:TextBox ID="a2_s" runat="server" ToolTip="String"/>
            </asp:TableCell>
            <asp:TableCell RowSpan="3">
                <asp:Button ID="sum_btn" runat="server" Text="=" OnClick="sum_btn_Click" />
            </asp:TableCell>
            <asp:TableCell>
                S:
                <asp:TextBox ID="result_s" runat="server" ReadOnly="true" />
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell>
                K:
                <asp:TextBox ID="a1_k" runat="server" ToolTip="Integer"/>
            </asp:TableCell>
            <asp:TableCell>
                K:
                <asp:TextBox ID="a2_k" runat="server" ToolTip="Integer"/>
            </asp:TableCell>
            <asp:TableCell>
                K:
                <asp:TextBox ID="result_k" runat="server" ReadOnly="true" />
            </asp:TableCell>
        </asp:TableRow>
        <asp:TableRow>
            <asp:TableCell>
                F:
                <asp:TextBox ID="a1_f" runat="server" ToolTip="Float"/>
            </asp:TableCell>
            <asp:TableCell>
                F:
                <asp:TextBox ID="a2_f" runat="server" ToolTip="Float"/>
            </asp:TableCell>
            <asp:TableCell>
                F:
                <asp:TextBox ID="result_f" runat="server" ReadOnly="true" />
            </asp:TableCell>
        </asp:TableRow>
    </asp:Table>
    <br />
    <asp:HyperLink runat="server" NavigateUrl="~/LabViews/Lab-04a.cshtml">
        Lab-04 Ajax
    </asp:HyperLink>

</asp:Content>
