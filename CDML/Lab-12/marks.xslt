<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="/">
        <html>
            <head>
                <title>Certification</title>
            </head>
            <body>
                <h1>Students:</h1>
                <table style="border:1px solid black;">
                    <thead>
                        <tr>
                            <th>Информация</th>
                            <th>Отметки</th>
                        </tr>
                    </thead>
                    <tbody>
                        <xsl:for-each select="certification/student">
                            <tr>
                                <td>
                                    <p>
                                        Фамилия:
                                        <xsl:value-of select="lastname" />
                                    </p>
                                    <p>
                                        Имя:
                                        <xsl:value-of select="firstname" />
                                    </p>
                                    <xsl:if test="fathername">
                                        <p>
                                            Отчество:
                                            <xsl:value-of select="fathername" />
                                        </p>
                                    </xsl:if>
                                    <p>
                                        Факультет:
                                        <xsl:value-of select="faculty" />
                                    </p>
                                    <p>
                                        Группа:
                                        <xsl:value-of select="group" />
                                    </p>
                                </td>
                                <td>
                                    <table>
                                        <thead>
                                            <tr>
                                                <th>Дисциплина</th>
                                                <th>Отметка</th>
                                            </tr>
                                        </thead>
                                        <tbody>
                                            <xsl:for-each select="marks/mark">
                                                <tr>
                                                    <td>
                                                        <xsl:value-of select="subject" />
                                                    </td>
                                                    <xsl:choose>
                                                        <xsl:when test="value &gt; 7">
                                                            <td style="background-color:#00ff00;text-align:center;">
                                                                <xsl:value-of select="value" />
                                                            </td>
                                                        </xsl:when>
                                                        <xsl:when test="value &lt; 5">
                                                            <td style="background-color:#ff0000;text-align:center;">
                                                                <xsl:value-of select="value" />
                                                            </td>
                                                        </xsl:when>
                                                        <xsl:otherwise>
                                                            <td style="text-align:center;">
                                                                <xsl:value-of select="value" />
                                                            </td>
                                                        </xsl:otherwise>
                                                    </xsl:choose>
                                                </tr>
                                            </xsl:for-each>
                                        </tbody>
                                    </table>
                                </td>
                            </tr>
                        </xsl:for-each>
                    </tbody>
                </table>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>