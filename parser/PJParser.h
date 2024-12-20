/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PJPARSER_H_INCLUDED
# define YY_YY_PJPARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_AND = 258,
    T_ELSE = 259,
    T_FLOAT = 260,
    T_FOR = 261,
    T_IF = 262,
    T_LONGINT = 263,
    T_BOOLEAN = 264,
    T_PROGRAM = 265,
    T_FUNCTION = 266,
    T_NOT = 267,
    T_OR = 268,
    T_READ = 269,
    T_WHILE = 270,
    T_WRITE = 271,
    T_WRITELN = 272,
    T_BEGIN = 273,
    T_END = 274,
    T_VAR = 275,
    T_DO = 276,
    T_ARRAY = 277,
    T_EXIT = 278,
    T_THEN = 279,
    T_LE = 280,
    T_LT = 281,
    T_GE = 282,
    T_GT = 283,
    T_EQ = 284,
    T_NE = 285,
    T_ASSIGN = 286,
    T_COMMA = 287,
    T_SEMICOLON = 288,
    T_COLON = 289,
    T_LBRACKET = 290,
    T_RBRACKET = 291,
    T_LPAREN = 292,
    T_RPAREN = 293,
    T_PLUS = 294,
    T_TIMES = 295,
    T_IDENTIFIER = 296,
    T_DIV = 297,
    T_STRING = 298,
    T_INTNUM = 299,
    T_FLOATNUM = 300,
    T_MINUS = 301,
    T_DOT = 302,
    T_DOTDOT = 303,
    T_OF = 304,
    T_TRUE = 305,
    T_FALSE = 306
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 369 "PJParser.y" /* yacc.c:1909  */
 
	int ival;
	char *sval;
	struct DLinkList_struct *dll;
	int *iarrval;

#line 113 "PJParser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PJPARSER_H_INCLUDED  */
