#include "ScpLex.h"
#include "ScpScriptLex.h"
#include "../Common/stdstringext.hpp"
ScpLex::ScpLex(std::string commandstring):startpos(0),Expression(commandstring)
{
	STDSTRINGEXT::trim(Expression);
}

ScpLex::~ScpLex(void)
{

}
std::string ScpLex::GetNextToken()
{
	if(startpos>=Expression.length())
	{
		return scpEndofExpression;		
	}	
	std::string LeftExp=Expression.substr(startpos,1);
	const char* pstr = LeftExp.data();
	while (isspace(*pstr))
	{
		startpos += 1;
		pstr += 1;		
	}
	LeftExp = Expression.substr(startpos, 1);
	//while(iswspace(*LeftExp.begin()))
	//{
	//	startpos+=1;
	//	LeftExp=Expression.substr(startpos,1);
	//}
	int pos =0;
	if(LeftExp==scpLeftParentheses)
	{
		startpos ++;
		return scpLeftParentheses;
	}
	else if (LeftExp==scpRightParentheses)
	{
		startpos ++;
		return scpRightParentheses;
	}		
	else if (LeftExp==scpOperationAdd)
	{		
		startpos ++;
		std::string token = Expression.substr(startpos,1);
		if(token==scpOperationAssign)
		{
			startpos ++;
			return scpOperationAddAndAssign;
		}
		else 
		{
			return scpOperationAdd;
		}		
	}
	else if (LeftExp==scpOperationSubtraction)
	{
		startpos ++;
		std::string token = Expression.substr(startpos,1);
		if(token==scpOperationAssign)
		{
			startpos ++;
			return scpOperationSubAndAssign;
		}
		else 
		{
			//原来是考虑判断是否是负号
			//因为如果没有左边的表达式，那它就是一个负值，而不是进行减法操作
			//if(objstack.size()!=0)
				return scpOperationSubtraction;
		}
	}
	else if (LeftExp==scpOperationMultiplication)
	{
		startpos ++;
		std::string token = Expression.substr(startpos,1);
		if(token==scpOperationAssign)
		{
			startpos ++;
			return scpOperationMulAndAssign;
		}
		else 
		{
			return scpOperationMultiplication;
		}
	}
	else if (LeftExp==scpOperationDivision)
	{
		startpos ++;
		std::string token = Expression.substr(startpos,1);
		if(token==scpOperationAssign)
		{
			startpos ++;
			return scpOperationDivAndAssign;
		}
		else 
		{
			return scpOperationDivision;
		}
	}
	else if (LeftExp==scpOperationMod)
	{
		startpos ++;
		std::string token = Expression.substr(startpos,1);
		if(token==scpOperationAssign)
		{
			startpos ++;
			return scpOpeartionModAndAssign;
		}
		else 
		{
			return scpOperationMod;
		}
	}
	else if (LeftExp==scpOperationAssign)
	{
		startpos ++;
		std::string token = Expression.substr(startpos,1);
		if(token==scpOperationAssign)
		{
			startpos ++;
			return scpOperationEqual;
		}
		else 
		{
			return scpOperationAssign;
		}
	}
	else if (LeftExp==scpOperationLessthan)
	{
		startpos ++;
		std::string token = Expression.substr(startpos,1);
		if(token==scpOperationAssign)
		{
			startpos ++;
			return scpOperationLessorEqual;
		}
		else if(token==scpOperationLessthan)
		{
			startpos ++;
			return scpOperationBitShiftLeft;
		}
		else 
		{
			return scpOperationLessthan;
		}
	}
	else if (LeftExp==scpOperationBigthan)
	{
		startpos ++;
		std::string token = Expression.substr(startpos,1);
		if(token==scpOperationAssign)
		{
			startpos ++;
			return scpOperationBigorEqual;
		}
		else if(token==scpOperationBigthan)
		{
			startpos ++;
			return scpOperationBitShiftRight;
		}
		else 
		{
			return scpOperationBigthan;
		}
	}
	else if (LeftExp == scpOperationNot)
	{
		startpos ++;
		std::string token = Expression.substr(startpos,1);
		if(token==scpOperationAssign)
		{
			startpos ++;
			return scpOperationNotEqual;
		}
		else 
		{
			return scpOperationNot;
		}
	}
	else if(LeftExp ==scpOperationBitAnd)
	{
		startpos ++;
		std::string token = Expression.substr(startpos,1);
		if(token==scpOperationBitAnd)
		{
			startpos ++;
			return scpOperationLogicalAnd;
		}
		else 
		{
			return scpOperationBitAnd;
		}
	}
	else if(LeftExp ==scpOperationBitOr)
	{
		startpos ++;
		std::string token = Expression.substr(startpos,1);
		if(token==scpOperationBitOr)
		{
			startpos ++;
			return scpOperationLogicalOr;
		}
		else 
		{
			return scpOperationBitOr;
		}
	}
	else if(LeftExp ==scpOperationBitNot)
	{
		startpos ++;
		return scpOperationBitOr;		
	}
	else if(LeftExp ==scpOperationBitXor)
	{
		startpos ++;
		return scpOperationBitXor;		
	}
	{
		pos = startpos;
		if (LeftExp==scpOperationSubtraction)
			pos--;
		int endpos = startpos;
		std::string::iterator it = Expression.begin();
		it+=startpos;
		while((it!=Expression.end())
			&&(*it!=scpOperationAdd[0])
			&&(*it!=scpOperationSubtraction[0])
			&&(*it!=scpOperationMultiplication[0])
			&&(*it!=scpOperationDivision[0])
			&&(*it!=scpOperationMod[0])
			&&(*it!=scpOperationAssign[0])
			&&(*it!=scpOperationLessthan[0])
			&&(*it!=scpOperationBigthan[0])
			&&(*it!=scpOperationNot[0])
			&&(*it!=scpOperationBitAnd[0])
			&&(*it!=scpOperationBitOr[0])
			&&(*it!=scpOperationBitNot[0])
			&&(*it!=scpOperationBitXor[0])
			&&(*it!=scpRightParentheses[0])
			)
		{
			endpos++;
			it++;
		}
		startpos = endpos;
		std::string temp = Expression.substr(pos,endpos-pos);
		return STDSTRINGEXT::trim(temp);
	}
}
std::string ScpLex::GetLastToken()
{
	return last;
}
std::string ScpLex::GetCurrentToken()
{
	return current;
}
BOOL ScpLex::IsUnaryOperator(std::string & Token)
{
	if (Token==scpOperationNot || Token == scpOperationBitNot || Token == scpOperationBitXor || Token == scpOperationObjectRefrence)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL ScpLex::IsBinaryOperator(std::string & token)
{
	BOOL bRet=FALSE;
	//std::string BinaryOperator;
	//BinaryOperator=scpOperationAdd+L"|";
	//BinaryOperator=scpOperationSubtraction+L"|";
	//BinaryOperator=scpOperationMultiplication+L"|";
	//BinaryOperator=scpOperationDivision+L"|";
	//BinaryOperator=scpOperationMod+L"|";
	//BinaryOperator=scpOperationEqual+L"|";
	//BinaryOperator=scpOperationLessthan+L"|";
	//BinaryOperator=scpOperationLessorEqual+L"|";
	//BinaryOperator=scpOperationBigthan+L"|";
	//BinaryOperator=scpOperationBigorEqual+L"|";
	//BinaryOperator=scpOperationNotEqual+L"|";
	//BinaryOperator=scpOperationBitAnd+L"|";
	//BinaryOperator=scpOperationBitOr+L"|";
	//BinaryOperator=scpOperationBitXor+L"|";
	//BinaryOperator=scpOperationLogicalAnd+L"|";
	//BinaryOperator=scpOperationLogicalOr+L"|";
	//BinaryOperator=scpOperationBitShiftLeft+L"|";
	//BinaryOperator=scpOperationBitShiftRight+L"|";
	//BinaryOperator=scpOperationAssign+L"|";
	//BinaryOperator=scpOperationAddAndAssign+L"|";
	//BinaryOperator=scpOperationSubAndAssign+L"|";
	//BinaryOperator=scpOperationMulAndAssign+L"|";
	//BinaryOperator=scpOperationDivAndAssign+L"|";
	//BinaryOperator=scpOpeartionModAndAssign;
    //	Regexp regexp(BinaryOperator.c_str());
//	if(regexp.Match(token.c_str()))
//	{
//		bRet = TRUE;
//	}
    if (token==scpOperationAdd
		||token==scpOperationSubtraction
		||token==scpOperationMultiplication
		||token==scpOperationDivision
		||token==scpOperationMod
		||token==scpOperationEqual
		||token==scpOperationLessthan
		||token==scpOperationLessorEqual
		||token==scpOperationBigthan
		||token==scpOperationBigorEqual
		||token==scpOperationNotEqual			
		||token ==scpOperationBitAnd
		||token ==scpOperationBitOr
		||token ==scpOperationBitXor
		||token ==scpOperationLogicalAnd
		||token ==scpOperationLogicalOr
		||token ==scpOperationBitShiftLeft
		||token ==scpOperationBitShiftRight
		||token==scpOperationAssign
		||token==scpOperationAddAndAssign
		||token==scpOperationSubAndAssign
		||token==scpOperationMulAndAssign
		||token==scpOperationDivAndAssign
		||token==scpOpeartionModAndAssign)
	{
		return TRUE;
	}
	return FALSE;
}