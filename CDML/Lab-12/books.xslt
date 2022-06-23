<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="/">
        <html>
            <head>
                <title>Books</title>
            </head>
            <body>
                <h1>Bookshelf:</h1>
                <table style="border:1px solid black;">
                    <thead>
                        <tr>
                            <th>Информация</th>
                            <th>Обложка</th>
                        </tr>
                    </thead>
                    <tbody>
                        <xsl:for-each select="shelf/book">
                            <tr>
                                <td>
                                    <p>
                                        Автор:
                                        <xsl:value-of select="author" />
                                    </p>
                                    <p>
                                        Название:
                                        <xsl:value-of select="title" />
                                    </p>
                                    <p>
                                        Издательство:
                                        <xsl:value-of select="publisher" />
                                    </p>
                                    <p>
                                        Год издания:
                                        <xsl:value-of select="year" />
                                    </p>
                                    <p>
                                        Кол-во страниц:
                                        <xsl:value-of select="pages" />
                                    </p>
                                </td>
                                <td>
                                    <img src="{cover}" style="height:192px"></img>
                                </td>
                            </tr>
                        </xsl:for-each>
                    </tbody>
                </table>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>