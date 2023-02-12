/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
*/
#ifndef _H_SCPRUNTIME
#define _H_SCPRUNTIME
#include "ScpObject.h"
#include "ScpObjectSpace.h"
//内置运算符

ScpObject * Add(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * Sub(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * Mul(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * Div(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * Mod(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * Assign( ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * Equal(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * Lessthan(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * LessorEqual(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * Bigthan(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * BigorEqual(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * Not(ScpObject * x, CScriptEngine * engine);
ScpObject * NotEqual(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * BitAnd(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * BitOr(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * BitNot(ScpObject * x, CScriptEngine * engine);
ScpObject * BitXor(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * LogicalAnd(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * LogicalOr(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * BitShiftLeft(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * BitShiftRight(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * AddAndAssign( ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * SubAndAssign( ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * MulAndAssign( ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * DivAndAssign( ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * ModAndAssign( ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * BitAndAndAssign(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * BitOrAndAssign(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * BitNotAndAssign(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * BitXorAndAssign(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * BitShiftLeftAndAssign(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * BitShiftRightAndAssign(ScpObject * x, ScpObject * y, CScriptEngine * engine);
ScpObject * Minus(ScpObject * x, CScriptEngine * engine);
ScpObject * PreSelfAdd(ScpObject * x, CScriptEngine * engine);
ScpObject * PostSelfAdd(ScpObject * x, CScriptEngine * engine);
ScpObject * PreSelfSub(ScpObject * x, CScriptEngine * engine);
ScpObject * PostSelfSub(ScpObject * x, CScriptEngine * engine);
#endif //_H_SCPRUNTIME