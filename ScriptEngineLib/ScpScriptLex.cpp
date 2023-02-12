/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//词法解析、命令行解析
*/
#include "ScpScriptLex.h"
#include "ScriptEngine.h"
#include "ScpGlobalObject.h"
#include "ScpObjectNammes.h"
#include "commanddefine_uni.h"
#include <locale>
#include "../Common/stdstringext.hpp"

bool isalnumlaut(const char character) {
	int cr = (int)(unsigned char)character;
	if (isalnum(character)
		|| cr == 195 // UTF-8
		|| cr == 132 // ?
		|| cr == 164 // ?
		|| cr == 150 // ?
		|| cr == 182 // ?
		|| cr == 156 // ?
		|| cr == 188 // ü
		|| cr == 159 // ?
		) {
		return true;
	}
	else {
		return false;
	}
}
ScpScriptLex::ScpScriptLex()
{
	

}
void ScpScriptLex::SetExpression(std::string& Expression)
{
	wcommandline = Expression;
	prevtoken.clear();
	currenttoken.clear();
	currentpos = wcommandline.begin();
}

ScpScriptLex::~ScpScriptLex(void)
{

}

void ScpScriptLex::Attach(CScriptEngine * eng)
{
	engine = eng;
}

BOOL ScpScriptLex::ParseCommandLine(std::string& wcommandstring, ULONG& commandvalue, VTPARAMETERS & vtparameters)
{
	wcommandline = wcommandstring;
	currenttoken = "";
	prevtoken = "";
	currentpos = wcommandline.begin();
	std::string token = GetNextToken(TRUE);
	if (token.empty())
	{
		return FALSE;
	}
	if (token == scpComment)
	{
		return FALSE;
	}
	commandvalue = engine->QueryCommandValue(token);
	if (commandvalue != -1 )
	{
		//if (commandvalue >= vl_maxbasecommand)
		//{
		//	commandvalue = vl_call;
		//	vtparameters.push_back(ScpGlobalObject::GetInstance()->GetTypeName(ObjFunction));
		//	vtparameters.push_back(token);
		//}
		//else if(engine->globalcommand.IsGlobalCommandFunction(token))
		//{
		//	commandvalue = vl_call;
		//	vtparameters.push_back(ScpGlobalObject::GetInstance()->GetTypeName(ObjFunction));
		//	vtparameters.push_back(token);
		//}
		//else
		{
			ScpObject* obj = engine->GetCurrentObjectSpace()->FindObject(token);
			if (obj && obj->GetType() == ObjFunction)
			{
				commandvalue = vl_call;
				vtparameters.push_back(ScpGlobalObject::GetInstance()->GetTypeName(ObjFunction));
				vtparameters.push_back(token);
			}
			if (obj && obj->GetType() == ObjCFunction)
			{
				commandvalue = vl_call;
				vtparameters.push_back(ScpGlobalObject::GetInstance()->GetTypeName(ObjCFunction));
				vtparameters.push_back(token);
			}
		}

		token = GetNextToken(TRUE);		

		//engine->globalcommand.GetGlobalCommandFunction(commandvalue);
		//if (commandvalue != vl_exit &&
		//	commandvalue != vl_end	&&
		//	commandvalue != vl_test &&
		//	commandvalue != vl_otherwise &&
		//	commandvalue != vl_while &&
		//	commandvalue != vl_continue	&&
		//	commandvalue != vl_return	&&
		//	commandvalue != vl_break)
		//{
		//	if (token == scpColon || token == ScpObjectNames::GetSingleInsatnce()->strScpColoncn)
		//	{
		//		engine->PrintError(ScpObjectNames::GetSingleInsatnce()->scpErrorInvalidScript);
		//		engine->PrintError(wcommandline);
		//		return FALSE;
		//	}				
		//}
		//这里是让 return:1 return(1) return 1 都可以正确的执行
		if (commandvalue == vl_return)
		{
			if((token == ":")|| (token == "("))
			{
				token = GetNextToken(TRUE);
			}			
		}
		else
			token = GetNextToken(TRUE);
		std::string combinedtoken;
/*		while (!token.empty())
		{
			if (token == scpComma ||
				token == ScpObjectNames::GetSingleInsatnce()->strScpCommacn)
			{
				if (!combinedtoken.empty())
					vtparameters.push_back(combinedtoken);
				combinedtoken = L"";
			}
			else
			{
				combinedtoken += token;
			}
			token = GetNextToken(TRUE);
		}
		if (!combinedtoken.empty())
		{
			vtparameters.push_back(combinedtoken);
		}	*/	
		int inParenthesesScop = 0;
		while (!token.empty())
		{
			if (token == scpLeftParentheses)
			{
				inParenthesesScop += 1;
				combinedtoken += token;
			}
			else if (token == scpRightParentheses)
			{
				inParenthesesScop -= 1;
				if(inParenthesesScop>=0)//右括号的嵌套深度小于零则将右括号抛弃
					combinedtoken += token;
			}
			else if (token == scpComma ||
				token == ScpObjectNames::GetSingleInsatnce()->strScpCommacn)
			{
				if (inParenthesesScop <= 0)
				{
					vtparameters.push_back(combinedtoken);
					combinedtoken = "";
				}
				else
				{
					combinedtoken += token;
				}
			}
			else
			{
				combinedtoken += token;
			}
			token = GetNextToken(TRUE);
		}
		if (!combinedtoken.empty())
		{
			vtparameters.push_back(combinedtoken);
		}
	}
	else
	{

		ScpObject* obj = engine->GetCurrentObjectSpace()->FindObject(token);

		if (obj && obj->GetType() == ObjCFunction)
		{
			if (PeekNextToken() != scpLeftParentheses)
			{
				commandvalue = vl_call;
				vtparameters.push_back(ScpGlobalObject::GetInstance()->GetTypeName(ObjCFunction));
			}
			else
				commandvalue = vl_compute;
			//vtparameters.push_back(token);
		}
		else
			commandvalue = vl_compute;
		std::string combinedtoken;
		int inParenthesesScop = 0;
		while (!token.empty())
		{
			if (token == scpLeftParentheses)
			{
				inParenthesesScop += 1;
				combinedtoken += token;
			}
			else if (token == scpRightParentheses)
			{
				inParenthesesScop -= 1;
				combinedtoken += token;
			}
			else if (token == scpComma ||
				token == ScpObjectNames::GetSingleInsatnce()->strScpCommacn)
			{
				if (inParenthesesScop <= 0)
				{
					vtparameters.push_back(combinedtoken);
					combinedtoken = "";
				}
				else
				{
					combinedtoken += token;
				}
			}
			else
			{
				combinedtoken += token;
			}
			token = GetNextToken(TRUE);
		}
		if (!combinedtoken.empty())
		{
			vtparameters.push_back(combinedtoken);
		}

	}
	return TRUE;
}

BOOL ScpScriptLex::IsUserFunction(std::string token)
{
	BOOL bRet = FALSE;
	ScpObject *usercommand = (ScpObject *)engine->GetCurrentObjectSpace()->FindObject(token);
	if (usercommand)
	{
		if (usercommand->GetType() == ObjFunction)
		{
			bRet = TRUE;
		}
	}
	return bRet;
}
BOOL ScpScriptLex::IsClassInstance(std::string token)
{
	BOOL bRet = FALSE;
	ScpObject *usercommand = (ScpObject *)engine->GetCurrentObjectSpace()->FindObject(token);
	if (usercommand)
	{
		if (usercommand->GetType() == ObjClassInstance)
		{
			bRet = TRUE;
		}
	}
	return bRet;
}
BOOL ScpScriptLex::IsOperator(std::string token)
{
	BOOL bRet = FALSE;
	if (token == scpOperationObjectRefrence ||
		token == scpLeftParentheses ||
		token == scpRightParentheses ||
		token == scpLeftBrace ||
		token == scpRightBrace ||
		token == scpLeftBracket ||
		token == scpRightBracket ||
		token == scpComment ||
		token == scpColon ||
		token == ScpObjectNames::GetSingleInsatnce()->strScpColoncn ||
		token == scpComma ||
		token == ScpObjectNames::GetSingleInsatnce()->strScpCommacn ||
		token == scpOperationAdd ||
		token == scpOperationAssign ||
		token == scpOperationSelfAdd ||
		token == scpOperationAddAndAssign ||
		token == scpOperationSubtraction ||
		token == scpOperationSubAndAssign ||
		token == scpOperationSelfSub ||
		token == scpOperationMultiplication ||
		token == scpOperationMulAndAssign ||
		token == scpOperationDivision ||
		token == scpOperationDivAndAssign ||
		token == scpCppComment ||
		token == scpOperationMod ||
		token == scpOpeartionModAndAssign ||
		token == scpOperationAssign ||
		token == scpOperationEqual ||
		token == scpOperationLessthan ||
		token == scpOperationLessorEqual ||
		token == scpOpeartionBitShiftLeftAndAssign ||
		token == scpOperationBitShiftLeft ||
		token == scpOperationBigthan ||
		token == scpOperationBigorEqual ||
		token == scpOpeartionBitShiftRightAndAssign ||
		token == scpOperationBitShiftRight ||
		token == scpOperationNot ||
		token == scpOperationNotEqual ||
		token == scpOperationBitAnd ||
		token == scpOperationBitAndAndAssign ||
		token == scpOperationLogicalAnd ||
		token == scpOperationBitOr ||
		token == scpOperationBitOrAndAssign ||
		token == scpOperationLogicalOr ||
		token == scpOperationBitNot ||
		token == scpOperationBitNotAndAssign ||
		token == scpOperationBitXor ||
		token == scpOperationBitXorAndAssign
		)
	{
		bRet = TRUE;
	}
	return bRet;

}
std::string  ScpScriptLex::PeekNextToken(BOOL Convert)
{
	std::string::iterator it = currentpos;
	std::string temptoken = GetNextToken(Convert);
	currentpos = it;
	return temptoken;
}
std::string ScpScriptLex::GetCurrentToken()
{
	return currenttoken;
}
std::string  ScpScriptLex::PeekNext2Token(BOOL Convert)
{
	std::string::iterator it = currentpos;
	std::string temptoken = GetNextToken(Convert);
	temptoken = GetNextToken(Convert);
	currentpos = it;
	return temptoken;
}
std::string ScpScriptLex::GetNextToken(BOOL Convert)
{
	prevtoken = currenttoken;
	std::string token;
	bool until_nextscpDoubleQuote = false;
	while (currentpos != wcommandline.end())
	{
		std::string temp;
		temp += char(*currentpos);
		if (Convert)
		{
			if (temp == strPathTag)
			{
				if (until_nextscpDoubleQuote)
				{
					if (char(*(currentpos + 1)) == scpDoubleQuote[0])
					{
						token += scpDoubleQuote;
						currentpos++; currentpos++;
						continue;
					}
					else if (char(*(currentpos + 1)) == '\\')
					{
						token += "\\";
						currentpos++; currentpos++;
						continue;
					}
					else if (char(*(currentpos + 1)) == 'r')
					{
						token += "\r";
						currentpos++; currentpos++;
						continue;
					}
					else if (char(*(currentpos + 1)) == 'n')
					{
						token += "\n";
						currentpos++; currentpos++;
						continue;
					}
					else if (char(*(currentpos + 1)) == 't')
					{
						token += "\t";
						currentpos++; currentpos++;
						continue;
					}
				}
			}
		}
		if (temp == scpDoubleQuote)
		{
			if (!until_nextscpDoubleQuote)
			{
				until_nextscpDoubleQuote = true;
				token+=temp;
				currentpos++;
				continue;
			}
			else
			{
				token+=temp;
				currentpos++;				
				break;
			}
		}
		if (!until_nextscpDoubleQuote)
		{
			if (isspace(*currentpos))
			{
				currentpos++;
				if (token.empty())
					continue;
				else
					break;
			}
			else if (temp == scpOperationObjectRefrence)
			{
				if (token.empty())
				{
					token = temp;
					currentpos++;
					break;
				}
				else
				{
					if (token.at(0) == scpOperationSubtraction[0])
					{
						token += temp;
						currentpos++;
						continue;
					}
					else if (isdigit(token.at(0)))
					{
						token += temp;
						currentpos++;
						continue;
					}
					else
					{
						break;
					}
				}
			}
			else if (temp == scpLeftParentheses ||
				temp == scpRightParentheses ||
				temp == scpLeftBrace ||
				temp == scpRightBrace ||
				temp == scpLeftBracket ||
				temp == scpRightBracket ||
				temp == scpComment ||
				temp == scpColon ||
				temp == ScpObjectNames::GetSingleInsatnce()->strScpColoncn ||
				temp == scpComma ||
				temp == ScpObjectNames::GetSingleInsatnce()->strScpCommacn
				)
			{
				if (token.empty())
				{
					token = temp;
					currentpos++;
					break;
				}
				else
				{
					break;
				}
			}
			else if (temp == scpOperationAdd)
			{
				if (token.empty())
				{
					//向前探查，是否是+=
					if (char(*(currentpos + 1)) == scpOperationAssign[0])
					{
						token = scpOperationAddAndAssign;
						currentpos++; currentpos++;
						break;
					}
					//向前探查，是否是++
					else if (char(*(currentpos + 1)) == scpOperationAdd[0])
					{
						token = scpOperationSelfAdd;
						currentpos++; currentpos++;
						break;
					}
					else
					{
						token = temp;
						currentpos++;
						break;
					}
				}
				else
				{
					break;
				}

			}
			else if (temp == scpOperationSubtraction)
			{
				if (token.empty())
				{
					//向前探查，是否是-=
					if (char(*(currentpos + 1)) == scpOperationAssign[0])
					{
						token = scpOperationSubAndAssign;
						currentpos++; currentpos++;
						break;
					}
					//向前探查，是否是--
					else if (char(*(currentpos + 1)) == scpOperationSubtraction[0])
					{
						token = scpOperationSelfSub;
						currentpos++; currentpos++;
						break;
					}
					else if (isdigit(*(currentpos + 1)))
					{
						std::string temp2 = GetPrevToken();
						if (temp2.empty() || temp2 == "(")
						{
							token += temp; currentpos++;
						}
						else
						{
							token = temp;
							currentpos++;
							break;
						}
					}
					else
					{
						token = temp;
						currentpos++;
						break;
					}
				}
				else
				{
					break;
				}

			}
			else if (temp == scpOperationMultiplication)
			{
				if (token.empty())
				{
					//向前探查，是否是*=
					if (char(*(currentpos + 1)) == scpOperationAssign[0])
					{
						token = scpOperationMulAndAssign;
						currentpos++; currentpos++;
						break;
					}
					else
					{
						token = temp;
						currentpos++;
						break;
					}
				}
				else
				{
					break;
				}

			}
			else if (temp == scpOperationDivision)
			{
				if (token.empty())
				{
					//向前探查，是否是/=
					if (char(*(currentpos + 1)) == scpOperationAssign[0])
					{
						token = scpOperationDivAndAssign;
						currentpos++; currentpos++;
						break;
					}
					//向前探查，是否是// C++风格的注释
					else if (char(*(currentpos + 1)) == scpOperationDivision[0])
					{
						currentpos = wcommandline.end();
						//token=scpCppComment;
						//currentpos++;currentpos++;
						break;
					}
					else
					{
						token = temp;
						currentpos++;
						break;
					}
				}
				else
				{
					break;
				}

			}
			else if (temp == scpOperationMod)
			{
				if (token.empty())
				{
					//向前探查，是否是%=
					if (char(*(currentpos + 1)) == scpOperationAssign[0])
					{
						token = scpOpeartionModAndAssign;
						currentpos++; currentpos++;
						break;
					}
					else
					{
						token = temp;
						currentpos++;
						break;
					}
				}
				else
				{
					break;
				}

			}
			else if (temp == scpOperationAssign)
			{
				if (token.empty())
				{
					//向前探查，是否是==
					if (char(*(currentpos + 1)) == scpOperationAssign[0])
					{
						token = scpOperationEqual;
						currentpos++; currentpos++;
						break;
					}
					else
					{
						token = temp;
						currentpos++;
						break;
					}
				}
				else
				{
					break;
				}

			}
			else if (temp == scpOperationLessthan)
			{
				if (token.empty())
				{
					//向前探查，是否是<=小于等于
					if (char(*(currentpos + 1)) == scpOperationAssign[0])
					{
						token = scpOperationLessorEqual;
						currentpos++; currentpos++;
						break;
					}
					//向前探查，是否是<<左移
					else if (char(*(currentpos + 1)) == scpOperationLessthan[0])
					{
						if (char(*(currentpos + 2)) == scpOperationAssign[0])
						{
							token = scpOpeartionBitShiftLeftAndAssign;
							currentpos++;
						}
						else
						{
							token = scpOperationBitShiftLeft;
						}
						currentpos++; currentpos++;
						break;
					}
					else
					{
						token = temp;
						currentpos++;
						break;
					}
				}
				else
				{
					break;
				}

			}
			else if (temp == scpOperationBigthan)
			{
				if (token.empty())
				{
					//向前探查，是否是>=大于等于
					if (char(*(currentpos + 1)) == scpOperationAssign[0])
					{
						token = scpOperationBigorEqual;
						currentpos++; currentpos++;
						break;
					}
					//向前探查，是否是>>右移
					else if (char(*(currentpos + 1)) == scpOperationBigthan[0])
					{
						if (char(*(currentpos + 2)) == scpOperationAssign[0])
						{
							token = scpOpeartionBitShiftRightAndAssign;
							currentpos++;
						}
						else
						{
							token = scpOperationBitShiftRight;
						}
						currentpos++; currentpos++;
						break;
					}
					else
					{
						token = temp;
						currentpos++;
						break;
					}
				}
				else
				{
					break;
				}

			}
			else if (temp == scpOperationNot)
			{
				if (token.empty())
				{
					//向前探查，是否是!=不等于
					if (char(*(currentpos + 1)) == scpOperationAssign[0])
					{
						token = scpOperationNotEqual;
						currentpos++; currentpos++;
						break;
					}
					else
					{
						token = temp;
						currentpos++;
						break;
					}
				}
				else
				{
					break;
				}

			}
			else if (temp == scpOperationBitAnd)
			{
				if (token.empty())
				{
					//向前探查，是否是&=
					if (char(*(currentpos + 1)) == scpOperationAssign[0])
					{
						token = scpOperationBitAndAndAssign;
						currentpos++; currentpos++;
						break;
					}
					else if (char(*(currentpos + 1)) == scpOperationBitAnd[0])
					{
						token = scpOperationLogicalAnd;
						currentpos++; currentpos++;
						break;
					}
					else
					{
						token = temp;
						currentpos++;
						break;
					}
				}
				else
				{
					break;
				}

			}
			else if (temp == scpOperationBitOr)
			{
				if (token.empty())
				{
					//向前探查，是否是|=
					if (char(*(currentpos + 1)) == scpOperationAssign[0])
					{
						token = scpOperationBitOrAndAssign;
						currentpos++; currentpos++;
						break;
					}
					else if (char(*(currentpos + 1)) == scpOperationBitOr[0])
					{
						token = scpOperationLogicalOr;
						currentpos++; currentpos++;
						break;
					}
					else
					{
						token = temp;
						currentpos++;
						break;
					}
				}
				else
				{
					break;
				}

			}
			else if (temp == scpOperationBitNot)
			{
				if (token.empty())
				{
					//向前探查，是否是~=
					if (char(*(currentpos + 1)) == scpOperationAssign[0])
					{
						token = scpOperationBitNotAndAssign;
						currentpos++; currentpos++;
						break;
					}
					else
					{
						token = temp;
						currentpos++;
						break;
					}
				}
				else
				{
					break;
				}

			}
			else if (temp == scpOperationBitXor)
			{
				if (token.empty())
				{
					//向前探查，是否是^=
					if (char(*(currentpos + 1)) == scpOperationAssign[0])
					{
						token = scpOperationBitXorAndAssign;
						currentpos++; currentpos++;
						break;
					}
					else
					{
						token = temp;
						currentpos++;
						break;
					}
				}
				else
				{
					break;
				}
			}
			else if (temp == scpSemicolon)
			{
				if (token.empty())
				{
					currentpos++;
					continue;
				}
				else
				{
					currentpos++;
					break;
				}
			}
			else
			{
				//标识符允许是可见字符，数字，下划线，@符号
				//忽略掉未定义的符号;?`'@$
#ifdef _WIN32
				//std::locale loc2("zh_CN.UTF-8");
				//if (std::isalnum((*currentpos), loc2)  || (*currentpos) == '_' || (*currentpos) == '@')
				if (!isspace(*currentpos) || (*currentpos) == '_' || (*currentpos) == '@')
#else
				if (!isspace(*currentpos) || (*currentpos) == '_' || (*currentpos) == '@')
#endif
				{
					token += (*currentpos);
					currentpos++;
				}
				else
				{
					currentpos++;
					if (token.empty())
					{
						continue;
					}
					else
					{
						break;
					}
				}
			}
		}
		else
		{
			token += (*currentpos);
			currentpos++;
		}
	}
	currenttoken = token;
	return currenttoken;
}
std::string ScpScriptLex::GetPrevToken()
{
	return prevtoken;
}
BOOL ScpScriptLex::IsUnaryOperator(std::string & Token)
{
	if (Token == scpOperationNot || 
		Token == scpOperationBitNot || 
		Token == scpOperationBitXor || 
		Token == scpOperationObjectRefrence ||
		Token == scpOperationSelfAdd ||
		Token == scpOperationSelfSub)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL ScpScriptLex::IsAssignOperator(std::string & token)
{
	if (token == scpOperationAssign
		|| token == scpOperationAddAndAssign
		|| token == scpOperationSubAndAssign
		|| token == scpOperationMulAndAssign
		|| token == scpOperationDivAndAssign
		|| token == scpOpeartionModAndAssign
		|| token == scpOperationBitAndAndAssign
		|| token == scpOperationBitOrAndAssign 
		|| token == scpOperationBitNotAndAssign
		|| token == scpOperationBitXorAndAssign
		|| token == scpOpeartionBitShiftLeftAndAssign
		|| token == scpOpeartionBitShiftRightAndAssign)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL ScpScriptLex::IsBinaryOperator(std::string & token)
{
	BOOL bRet = FALSE;
	if (token == scpOperationAdd
		|| token == scpOperationSubtraction
		|| token == scpOperationMultiplication
		|| token == scpOperationDivision
		|| token == scpOperationMod
		|| token == scpOperationEqual
		|| token == scpOperationLessthan
		|| token == scpOperationLessorEqual
		|| token == scpOperationBigthan
		|| token == scpOperationBigorEqual
		|| token == scpOperationNotEqual
		|| token == scpOperationBitAnd
		|| token == scpOperationBitOr
		|| token == scpOperationBitXor
		|| token == scpOperationLogicalAnd
		|| token == scpOperationLogicalOr
		|| token == scpOperationBitShiftLeft
		|| token == scpOperationBitShiftRight
		)
	{
		return TRUE;
	}
	return FALSE;
}
int ScpScriptLex::GetOperationPriority(std::string &strOperation)
{
	//获得运算符的优先级，数值越小，优先级越高，-1为非法，
	int priority = -1;
	if (strOperation == scpOperationSelfAdd
		|| strOperation == scpOperationMinus
		|| strOperation == scpOperationSelfSub
		|| strOperation == scpOperationNot
		|| strOperation == scpOperationBitNot)
	{
		return 2;
	}
	return priority;
}
int ScpScriptLex::GetBinaryOperationPriority(std::string &strOperation)
{
	//获得运算符的优先级，数值越小，优先级越高，-1为非法，
	int priority = -1;
	if (strOperation == scpOperationMultiplication
		|| strOperation == scpOperationDivision
		|| strOperation == scpOperationMod)
	{
		return 3;
	}
	else if (strOperation == scpOperationAdd
		|| strOperation == scpOperationSubtraction)
	{
		return 4;
	}
	else if (strOperation == scpOperationBitShiftLeft
		|| strOperation == scpOperationBitShiftRight)
	{
		return 5;
	}
	else if (strOperation == scpOperationLessthan
		|| strOperation == scpOperationLessorEqual
		|| strOperation == scpOperationBigthan
		|| strOperation == scpOperationBigorEqual)
	{
		return 6;
	}
	else if (strOperation == scpOperationEqual
		|| strOperation == scpOperationNotEqual)
	{
		return 7;
	}
	else if (strOperation == scpOperationBitAnd)
	{
		return 8;
	}
	else if (strOperation == scpOperationBitXor)
	{
		return 9;
	}
	else if (strOperation == scpOperationBitOr)
	{
		return 10;
	}
	else if (strOperation == scpOperationLogicalAnd)
	{
		return 11;
	}
	else if (strOperation == scpOperationLogicalOr)
	{
		return 12;
	}
	else if (strOperation == scpOperationAssign
		|| strOperation == scpOperationAddAndAssign
		|| strOperation == scpOperationSubAndAssign
		|| strOperation == scpOperationMulAndAssign
		|| strOperation == scpOperationDivAndAssign
		|| strOperation == scpOpeartionModAndAssign 
		|| strOperation == scpOperationBitAndAndAssign
		|| strOperation == scpOperationBitOrAndAssign
		|| strOperation == scpOperationBitNotAndAssign
		|| strOperation == scpOperationBitXorAndAssign
		|| strOperation == scpOpeartionBitShiftLeftAndAssign
		|| strOperation == scpOpeartionBitShiftRightAndAssign)
	{
		return 13;
	}
	return priority;
}