#include <string.h>
int floaterror(char* err);
int floatlex();
void error(char* s, int tp);
extern float fnums[];
extern int fvnum;
float frval;
typedef unsigned char yytype_uint8;
typedef signed char yytype_int8;
typedef unsigned short int yytype_uint16;
typedef short int yytype_int16;
void* malloc(long unsigned int);
void free(void*);
union yyalloc
{
	yytype_int16 yyss_alloc;
	double yyvs_alloc;
};
static const yytype_uint8 yytranslate[] =
{
	   0, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 14, 2, 4, 2, 2, 2, 2,
	   2, 2, 11, 9, 2, 10, 2, 12, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   5, 3, 6, 2, 2, 2, 2, 2, 16, 2,
	   2, 7, 2, 2, 2, 2, 8, 2, 13, 2,
	   2, 2, 15, 2, 2, 2, 2, 2, 2, 2,
	   2, 18, 2, 19, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 17, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	   2, 2, 2, 2, 2, 2, 1, 2
};
static const yytype_uint8 yyr1[] =
{
	   0, 20, 21, 22, 22, 22, 22, 22, 22, 22,
	  22, 22, 22, 22, 22, 22, 22
};
static const yytype_uint8 yyr2[] =
{
	   0, 2, 1, 1, 2, 2, 3, 3, 3, 3,
	   3, 3, 3, 3, 3, 3, 3
};
static const yytype_uint8 yydefact[] =
{
	   0, 0, 0, 3, 0, 0, 2, 5, 4, 0,
	   1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   0, 16, 14, 15, 10, 11, 13, 12, 6, 7,
	   8, 9
};
static const yytype_int8 yydefgoto[] =
{
	  -1, 5, 6
};
static const yytype_int8 yypact[] =
{
	  37, 37, 37, -6, 37, 2, 34, -6, -6, 17,
	  -6, 37, 37, 37, 37, 37, 37, 37, 37, 37,
	  37, -6, -5, -5, -5, -5, -5, -5, -3, -3,
	  -6, -6
};
static const yytype_int8 yypgoto[] =
{
	  -6, -6, -1
};
static const yytype_uint8 yytable[] =
{
	   7, 8, 10, 9, 17, 18, 19, 20, 19, 20,
	  22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	  11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	   0, 0, 0, 0, 0, 0, 21, 11, 12, 13,
	  14, 15, 16, 17, 18, 19, 20, 1, 0, 0,
	   2, 0, 0, 0, 3, 4
};
static const yytype_int8 yycheck[] =
{
	   1, 2, 0, 4, 9, 10, 11, 12, 11, 12,
	  11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	   3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
	  -1, -1, -1, -1, -1, -1, 19, 3, 4, 5,
	   6, 7, 8, 9, 10, 11, 12, 10, -1, -1,
	  13, -1, -1, -1, 17, 18
};
static const yytype_uint8 yystos[] =
{
	   0, 10, 13, 17, 18, 21, 22, 22, 22, 22,
	   0, 3, 4, 5, 6, 7, 8, 9, 10, 11,
	  12, 19, 22, 22, 22, 22, 22, 22, 22, 22,
	  22, 22
};
static void
yydestruct(const char* yymsg, int yytype, double* yyvaluep)
{
	((void)(yyvaluep));
	if (!yymsg)
		yymsg = "Deleting";
	;
	switch (yytype)
	{
		default:
			break;
	}
}
int floatparse(void);
int floatchar;
double floatlval;
int floatnerrs;
int
floatparse(void)
{
	int yystate;
	int yyerrstatus;
	yytype_int16 yyssa[200];
	yytype_int16* yyss;
	yytype_int16* yyssp;
	double yyvsa[200];
	double* yyvs;
	double* yyvsp;
	long unsigned int yystacksize;
	int yyn;
	int yyresult;
	int yytoken;
	double yyval;
	int yylen = 0;
	yytoken = 0;
	yyss = yyssa;
	yyvs = yyvsa;
	yystacksize = 200;
	;
	yystate = 0;
	yyerrstatus = 0;
	floatnerrs = 0;
	floatchar = (-2);
	yyssp = yyss;
	yyvsp = yyvs;
	goto yysetstate;
yynewstate:
	yyssp++;
yysetstate:
	*yyssp = yystate;
	if (yyss + yystacksize - 1 <= yyssp)
	{
		long unsigned int yysize = yyssp - yyss + 1;
		if (10000 <= yystacksize)
			goto yyexhaustedlab;
		yystacksize *= 2;
		if (10000 < yystacksize)
			yystacksize = 10000;
		{
			yytype_int16* yyss1 = yyss;
			union yyalloc* yyptr =
				(union yyalloc*)malloc(((yystacksize) * (sizeof(yytype_int16) + sizeof(double)) + (sizeof(union yyalloc) - 1)));
			if (!yyptr)
				goto yyexhaustedlab;
			do { long unsigned int yynewbytes; memcpy(&yyptr->yyss_alloc, yyss, (yysize) * sizeof(*(yyss))); yyss = &yyptr->yyss_alloc; yynewbytes = yystacksize * sizeof(*yyss) + (sizeof(union yyalloc) - 1); yyptr += yynewbytes / sizeof(*yyptr); } while ((0));
			do { long unsigned int yynewbytes; memcpy(&yyptr->yyvs_alloc, yyvs, (yysize) * sizeof(*(yyvs))); yyvs = &yyptr->yyvs_alloc; yynewbytes = yystacksize * sizeof(*yyvs) + (sizeof(union yyalloc) - 1); yyptr += yynewbytes / sizeof(*yyptr); } while ((0));
			if (yyss1 != yyssa)
				free(yyss1);
		}
		yyssp = yyss + yysize - 1;
		yyvsp = yyvs + yysize - 1;
		;
		if (yyss + yystacksize - 1 <= yyssp)
			goto yyabortlab;
	}
	;
	if (yystate == 10)
		goto yyacceptlab;
	goto yybackup;
yybackup:
	yyn = yypact[yystate];
	if (yyn == -6)
		goto yydefault;
	if (floatchar == (-2))
	{
		;
		floatchar = floatlex();
	}
	if (floatchar <= 0)
	{
		floatchar = yytoken = 0;
		;
	}
	else
	{
		yytoken = ((unsigned int)(floatchar) <= 257 ? yytranslate[floatchar] : 2);
		;
	}
	yyn += yytoken;
	if (yyn < 0 || 55 < yyn || yycheck[yyn] != yytoken)
		goto yydefault;
	yyn = yytable[yyn];
	if (yyn <= 0)
	{
		if (yyn == 0 || yyn == -1)
			goto yyerrlab;
		yyn = -yyn;
		goto yyreduce;
	}
	if (yyerrstatus)
		yyerrstatus--;
	;
	floatchar = (-2);
	yystate = yyn;
	*++yyvsp = floatlval;
	goto yynewstate;
yydefault:
	yyn = yydefact[yystate];
	if (yyn == 0)
		goto yyerrlab;
	goto yyreduce;
yyreduce:
	yylen = yyr2[yyn];
	yyval = yyvsp[1 - yylen];
	;
	switch (yyn)
	{
		case 2:
		{ frval = (yyvsp[(1) - (1)]); ; }
		break;
		case 3:
		{(yyval) = fnums[fvnum++]; ; }
		break;
		case 4:
		{(yyval) = !(yyvsp[(2) - (2)]); ; }
		break;
		case 5:
		{(yyval) = -((yyvsp[(2) - (2)])); ; }
		break;
		case 6:
		{(yyval) = (yyvsp[(1) - (3)]) + (yyvsp[(3) - (3)]); ; }
		break;
		case 7:
		{(yyval) = (yyvsp[(1) - (3)]) - (yyvsp[(3) - (3)]); ; }
		break;
		case 8:
		{(yyval) = (yyvsp[(1) - (3)]) * (yyvsp[(3) - (3)]); ; }
		break;
		case 9:
		{(yyval) = (yyvsp[(1) - (3)]) / (yyvsp[(3) - (3)]); ; }
		break;
		case 10:
		{(yyval) = ((yyvsp[(1) - (3)]) < (yyvsp[(3) - (3)])); ; }
		break;
		case 11:
		{(yyval) = ((yyvsp[(1) - (3)]) > (yyvsp[(3) - (3)])); ; }
		break;
		case 12:
		{(yyval) = ((yyvsp[(1) - (3)]) <= (yyvsp[(3) - (3)])); ; }
		break;
		case 13:
		{(yyval) = ((yyvsp[(1) - (3)]) >= (yyvsp[(3) - (3)])); ; }
		break;
		case 14:
		{(yyval) = ((yyvsp[(1) - (3)]) == (yyvsp[(3) - (3)])); ; }
		break;
		case 15:
		{(yyval) = ((yyvsp[(1) - (3)]) != (yyvsp[(3) - (3)])); ; }
		break;
		case 16:
		{(yyval) = (yyvsp[(2) - (3)]);; }
		break;
		default: break;
	}
	;
	(yyvsp -= (yylen), yyssp -= (yylen));
	yylen = 0;
	;
	*++yyvsp = yyval;
	yyn = yyr1[yyn];
	yystate = yypgoto[yyn - 20] + *yyssp;
	if (0 <= yystate && yystate <= 55 && yycheck[yystate] == *yyssp)
		yystate = yytable[yystate];
	else
		yystate = yydefgoto[yyn - 20];
	goto yynewstate;
yyerrlab:
	if (!yyerrstatus)
	{
		++floatnerrs;
		floaterror("syntax error");
	}
	if (yyerrstatus == 3)
	{
		if (floatchar <= 0)
		{
			if (floatchar == 0)
				goto yyabortlab;
		}
		else
		{
			yydestruct("Error: discarding",
				yytoken, &floatlval);
			floatchar = (-2);
		}
	}
	goto yyerrlab1;
yyerrorlab:
	if (0)
		goto yyerrorlab;
	(yyvsp -= (yylen), yyssp -= (yylen));
	yylen = 0;
	;
	yystate = *yyssp;
	goto yyerrlab1;
yyerrlab1:
	yyerrstatus = 3;
	for (;;)
	{
		yyn = yypact[yystate];
		if (yyn != -6)
		{
			yyn += 1;
			if (0 <= yyn && yyn <= 55 && yycheck[yyn] == 1)
			{
				yyn = yytable[yyn];
				if (0 < yyn)
					break;
			}
		}
		if (yyssp == yyss)
			goto yyabortlab;
		yydestruct("Error: popping",
			yystos[yystate], yyvsp);
		(yyvsp -= (1), yyssp -= (1));
		yystate = *yyssp;
		;
	}
	*++yyvsp = floatlval;
	;
	yystate = yyn;
	goto yynewstate;
yyacceptlab:
	yyresult = 0;
	goto yyreturn;
yyabortlab:
	yyresult = 1;
	goto yyreturn;
yyexhaustedlab:
	floaterror("memory exhausted");
	yyresult = 2;
yyreturn:
	if (floatchar != (-2))
		yydestruct("Cleanup: discarding lookahead",
			yytoken, &floatlval);
	(yyvsp -= (yylen), yyssp -= (yylen));
	;
	while (yyssp != yyss)
	{
		yydestruct("Cleanup: popping",
			yystos[*yyssp], yyvsp);
		(yyvsp -= (1), yyssp -= (1));
	}
	if (yyss != yyssa)
		free(yyss);
	return (yyresult);
}
