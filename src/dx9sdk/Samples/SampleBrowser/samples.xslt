<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
	<xsl:template match="/">
	<table width="97%" border="0" cellpadding="0" cellspacing="0">
		<xsl:for-each select="//sample" order-by="name">
			<tr>
			<td valign="top" width="100%">
				<a>

				<xsl:attribute name="class">
				<xsl:choose>
					<xsl:when test="@installed[.='no']">name_notinstalled</xsl:when>
					<xsl:otherwise>name_installed</xsl:otherwise>
				</xsl:choose>
				</xsl:attribute>

				<xsl:if test="exe[.!='']">
					<xsl:attribute name="href">..\..\"<xsl:value-of	select="exefolder"/><xsl:value-of select="exe"/>"</xsl:attribute>
					<xsl:attribute name="title">..\..\<xsl:value-of	select="exefolder"/><xsl:value-of select="exe"/></xsl:attribute>
				</xsl:if>

				<xsl:value-of select="name"/>

				</a>

				<img class="language" hspace="5" width="19" height="19">
				<xsl:choose>
					<xsl:when test="language[.='Executable-Only']"><xsl:attribute name="src">img/spacer.gif</xsl:attribute></xsl:when>
					<xsl:when test="language[.='C++']"><xsl:attribute name="src">img/lang_cpp.gif</xsl:attribute></xsl:when>
					<xsl:when test="language[.='C#']"><xsl:attribute name="src">img/lang_cs.gif</xsl:attribute></xsl:when>
					<xsl:when test="language[.='VB.Net']"><xsl:attribute name="src">img/lang_vb.gif</xsl:attribute></xsl:when>
				</xsl:choose>
				</img>
			</td>
			<td valign="top" align="right">
				<table cellpadding="0" cellspacing="0" border="0">
				<tr>
					<td>
					<xsl:if test="complexity[. > 0]">
						<img class="difficulty" width="90" height="19" hspace="10">
						<xsl:choose>
							<xsl:when test="complexity[. > 1999]"><xsl:attribute name="src">img/diff_advanced.gif</xsl:attribute></xsl:when>
							<xsl:when test="complexity[. > 999]"><xsl:attribute name="src">img/diff_intermediate.gif</xsl:attribute></xsl:when>
							<xsl:otherwise><xsl:attribute name="src">img/diff_beginner.gif</xsl:attribute></xsl:otherwise>
						</xsl:choose>
						</img>
					</xsl:if>
					</td>
					<td>
					<img class="difficulty" width="90" height="19">
						<xsl:choose>
							<xsl:when test="type[.='sample']"><xsl:attribute name="src">img/type_sample.gif</xsl:attribute></xsl:when>
							<xsl:when test="type[.='tutorial']"><xsl:attribute name="src">img/type_tutorial.gif</xsl:attribute></xsl:when>
							<xsl:when test="type[.='demo']"><xsl:attribute name="src">img/type_demo.gif</xsl:attribute></xsl:when>
							<xsl:when test="type[.='utility']"><xsl:attribute name="src">img/type_utility.gif</xsl:attribute></xsl:when>
						</xsl:choose>
					</img>
					</td>
				</tr>
				</table>
			</td>
			<td rowspan="4" valign="top" align="right">
				<xsl:attribute name="class">
				<xsl:choose>
					<xsl:when test="screenshot[.!='']">Screenshot</xsl:when>
					<xsl:otherwise>noScreenshot</xsl:otherwise>
				</xsl:choose>
				</xsl:attribute>

				<img hspace="10" width="78" height="12" style="position: relative; top: -12px; left: -10px;">
				<xsl:choose>
					<xsl:when test="@installed[.='no']"><xsl:attribute name="src">img\results_not_installed.gif</xsl:attribute></xsl:when>
					<xsl:otherwise><xsl:attribute name="src">img\spacer.gif</xsl:attribute></xsl:otherwise>
				</xsl:choose>
				</img>

				<a>
				<xsl:if test="exe[.!='']">
				<xsl:attribute name="href">..\..\"<xsl:value-of select="exefolder"/><xsl:value-of select="exe"/>"</xsl:attribute>
				<xsl:attribute name="title">..\..\<xsl:value-of select="exefolder"/><xsl:value-of select="exe"/></xsl:attribute>
				</xsl:if>

				<xsl:if test="screenshot[.!='']">
				<img width="90" border="0" onError="style.display = 'None'" style="position: relative; top: -5px">
					<xsl:attribute name="src">
					..\..\<xsl:value-of select="folder"/><xsl:value-of select="screenshot"/>
					</xsl:attribute>
				</img>
				</xsl:if>
				</a>
			</td>
			</tr>
			<tr>
			<td colspan="2" valign="top"><p class="description_highlight"></p></td>
			</tr>
			<tr>
			<td colspan="2" valign="top"><p class="description"><xsl:value-of select="description"/></p><p></p></td>
			</tr>
			<tr>
			<td colspan="2" valign="top" height="30" style="padding-left: 22px">
				<xsl:if test="exe[.!='']">
				<a class="links">
				<xsl:attribute name="href">..\..\"<xsl:value-of select="exefolder"/><xsl:value-of select="exe"/>"</xsl:attribute>
				<xsl:attribute name="title">..\..\<xsl:value-of select="exefolder"/><xsl:value-of select="exe"/></xsl:attribute>Executable<font style="text-decoration: none">&#160;</font></a>
				</xsl:if>

				<xsl:if test="doc[.!='']">
				<a class="links">
					<xsl:choose>
					<xsl:when test="language[.='Executable-Only']">
						<xsl:attribute name="href"><xsl:value-of select="doc"/></xsl:attribute>
						<xsl:attribute name="title"><xsl:value-of select="doc"/></xsl:attribute>
					</xsl:when>

					<xsl:when test="language[.='C++']">
						<xsl:attribute name="href">ms-its:../../Doc/DirectX9/directx9_c.chm<xsl:value-of select="doc"/></xsl:attribute>
						<xsl:attribute name="title">../../Doc/DirectX9/directx9_c.chm<xsl:value-of select="doc"/></xsl:attribute>
					</xsl:when>

					<xsl:otherwise>
						<xsl:attribute name="href">..\..\"<xsl:value-of select="folder"/><xsl:value-of select="doc"/>"</xsl:attribute>
						<xsl:attribute name="title">..\..\<xsl:value-of select="folder"/><xsl:value-of select="doc"/></xsl:attribute>
					</xsl:otherwise>
					</xsl:choose>
					Documentation<font style="text-decoration: none">&#160;</font></a>
				</xsl:if>

				<xsl:choose>
				<xsl:when test="projectfile6[.!='']">
					<a class="links">
					<xsl:attribute name="href">..\..\"<xsl:value-of select="folder"/><xsl:value-of select="projectfile6"/>
					<xsl:if test="projectfile7[.!='']">*<xsl:value-of select="folder"/><xsl:value-of select="projectfile7"/></xsl:if>"
					</xsl:attribute>Project&#160;Files<font style="text-decoration: none">&#160;</font></a>
				</xsl:when>
				<xsl:otherwise>
					<xsl:if test="projectfile7[.!='']">
						<a class="links">
						<xsl:attribute name="href">..\..\"<xsl:value-of select="folder"/><xsl:value-of select="projectfile7"/>"
						</xsl:attribute>Project&#160;Files<font style="text-decoration: none">&#160;</font></a>
					</xsl:if>
				</xsl:otherwise>
				</xsl:choose>
			</td>
			</tr>
		</xsl:for-each>
	</table>
	</xsl:template>
</xsl:stylesheet>
