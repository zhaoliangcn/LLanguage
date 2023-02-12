/*
//author :zhaoliang
//email:zhaoliangcn@126.com
//code descriptyon:
//对象作用域空间管理，用于实现名字空间的隔离
*/
#include "ScpObjectSpace.h"
#include "ScpTableObject.h"
#include "ScpArrayObject.h"
#include "ScpClassObject.h"
#include "ScpClassInstanceObject.h"
#include "ScpStructObject.h"
#include "ScpObjectFactory.h"
#include "ScpCommonObject.h"
#include "../Common/stdstringext.hpp"
#include <time.h>
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#ifdef WIN32
int gettimeofday(struct timeval *tp, void *tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}
#endif

//产生长度为length的随机字符串
int genRandomString2(int length, char* ouput)
{
	int flag, i;
	struct timeval tpstart;
	gettimeofday(&tpstart, NULL);
	srand(tpstart.tv_usec);
	for (i = 0; i < length - 1; i++)
	{
		flag = rand() % 3;
		switch (flag)
		{
		case 0:
			ouput[i] = 'A' + rand() % 26;
			break;
		case 1:
			ouput[i] = 'a' + rand() % 26;
			break;
		case 2:
			ouput[i] = '0' + rand() % 10;
			break;
		default:
			ouput[i] = 'x';
			break;
		}
	}
	return 0;
}
std::string GenRandomString1()
{
	const int SIZE_CHAR = 32; //生成32 + 1位C Style字符串
	const char CCH[] = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
#ifdef _WIN32
	srand((unsigned)GetTickCount64());
#else 
	srand((unsigned)time(NULL));
#endif
	char ch[SIZE_CHAR + 1] = { 0 };
	for (int i = 0; i < SIZE_CHAR; ++i)
	{
		int x = rand() / (RAND_MAX / (sizeof(CCH) - 1));
		ch[i] = CCH[x];
	}
	return std::string("temp")+ch;
}
std::string GenRandomString()
{
	const int SIZE_CHAR = 32; //生成32 + 1位C Style字符串
	char ch[SIZE_CHAR + 1] = { 0 };
	genRandomString2(SIZE_CHAR, ch);
	return std::string("temp") + ch;
}
ScpObjectSpace::ScpObjectSpace(void):breakingout(0),continuewhile(0),parentspace(NULL),enddepths(0),lastTestResult(-1),LastTempObjAppendix(0),lastcommand(0),LastTempObjectName("@@tempobj")
{
	breakingout = 0  ;
	continuewhile =  0 ;
	parentspace = NULL;
	//LastTempObjectName = "@@tempobj";
	LastTempObjectName = STDSTRINGEXT::Format("@@tempobj%d", ScpRandomNumberObject::GetRandom().value);
	enddepths = 0;
	lastTestResult =-1;
	LastTempObjAppendix =0;
	lastcommand = 0;
}

ScpObjectSpace::~ScpObjectSpace(void)
{
	DestroyTempObjects();
}
ScpObject * ScpObjectSpace::FindStructMemberVariable(const std::string& objname)
{
	size_t pos = objname.find(scpOperationObjectRefrence);
	if(pos!=std::string::npos)
	{
		std::string parent;
		std::string children;
		parent=objname.substr(0,pos);
		children=objname.substr(pos+1,objname.length()-pos-1);
		ScpObject* parentobj = FindObject(parent);
		if(parentobj)
		{
			if(parentobj->GetType()==ObjStructInstance)
			{
				ScpStructInstanceObject* structobj=(ScpStructInstanceObject* )parentobj;
				if(structobj)
				{
					ScpObject * childobj = structobj->StructObjectSpace.FindLocalObject(children);
					return childobj;
				}
			}
		}
	}
	return NULL;
}
ScpObject * ScpObjectSpace::FindClassOrStructMemberVariable(const std::string & objname)
{
	size_t pos = objname.find(scpOperationObjectRefrence);
	if (pos != std::string::npos)
	{
		std::string parent;
		std::string children;
		parent = objname.substr(0, pos);
		children = objname.substr(pos + 1, objname.length() - pos - 1);
		ScpObject* parentobj = FindObject(parent);
		if (parentobj)
		{
			if (parentobj->GetType() == ObjClassInstance)
			{
				ScpClassObject* classobj = (ScpClassObject*)parentobj;
				if (classobj)
				{
					ScpObject * childobj = classobj->UserClassObjectSpace.FindLocalObject(children);
					if (childobj)
					{
						if (classobj->memberattrmap[children] == ScpClassObject::Attr_Public)
						{
							return childobj;
						}
						else
						{
							return NULL;
						}
					}
				}
			}
			else
			{
				if (parentobj->GetType() == ObjStructInstance)
				{
					ScpStructInstanceObject* structobj = (ScpStructInstanceObject*)parentobj;
					if (structobj)
					{
						ScpObject * childobj = structobj->StructObjectSpace.FindLocalObject(children);
						return childobj;
					}
				}
			}
		}
	}
	return NULL;
}
ScpObject * ScpObjectSpace::FindClassMemberVariable(const std::string& objname)
{
	//size_t pos = objname.find(scpColon);
	//if(pos==std::wstring::npos)
	//{
	//	pos=objname.find(ScpObjectNames::GetSingleInsatnce()->strScpColoncn);
	//}
	//if(pos==std::wstring::npos)
	//{
	//	pos = objname.find(scpOperationObjectRefrence);
	//}
	size_t pos = objname.find(scpOperationObjectRefrence);
	if(pos!=std::string::npos)
	{
		std::string parent;
		std::string children;
		parent=objname.substr(0,pos);
		children=objname.substr(pos+1,objname.length()-pos-1);
		ScpObject* parentobj = FindObject(parent);
		if(parentobj)
		{
			if(parentobj->GetType()==ObjClassInstance)
			{
				ScpClassObject* classobj=(ScpClassObject* )parentobj;
				if(classobj)
				{
					ScpObject * childobj = classobj->UserClassObjectSpace.FindLocalObject(children);
					if(childobj)
					{
						if(classobj->memberattrmap[children]==ScpClassObject::Attr_Public)
						{
							return childobj;
						}
						else
						{
							return NULL;
						}						
					}
				}
			}
		}
	}
	return NULL;
}
ScpObject * ScpObjectSpace::FindTableElement(const std::string& objname)
{
	size_t pos1 = objname.find(scpLeftBracket);
	if((pos1!=std::string::npos))
	{
		size_t pos2=objname.length()-1;
		if(scpRightBracket==objname.substr(pos2,1))
		{			
			std::string name = objname.substr(0,pos1);
			std::string element = objname.substr(pos1+1,pos2-pos1-1);			
			if(element.substr(element.length()-1,1)==scpRightBracket)
			{
				return FindTableElement(element);
			}
			else
			{
				if(IsStaticNumber(element))
				{
					int Index = StringToInt(element.c_str());
					ScpObject* tableobj=FindObject(name);
					if(tableobj)
					{
						if(tableobj->GetType()==ObjTable)
						{
							ScpObject * childobj = ((ScpTableObject* )tableobj)->GetElement(Index);
							if(childobj)
							{
								return childobj;
							}
						}
					}
				}	
				else
				{
					ScpObject* tableobj=FindObject(name);
					if(tableobj)
					{
						if(tableobj->GetType()==ObjTable)
						{							
							ScpObject * childobj = ((ScpTableObject* )tableobj)->GetElement(element);
							if(childobj)
							{
								return childobj;
							}
							ScpObject * obj = FindObject(element);
							if(obj && obj->GetType()==ObjInt)
							{
								int Index =((ScpIntObject *)obj)->value;
								return ((ScpTableObject* )tableobj)->GetElement(Index);
							}
						}
					}
				}
			}
		}
	}	
	return NULL;
}
ScpObject * ScpObjectSpace::FindArrayElement(const std::string& objname)
{
	size_t pos1 = objname.find(scpLeftBracket);
	if((pos1!=std::string::npos))
	{
		size_t pos2=objname.length()-1;
		if(scpRightBracket==objname.substr(pos2,1))
		{
			std::string arrayname = objname.substr(0,pos1);
			std::string arrayelement = objname.substr(pos1+1,pos2-pos1-1);
			if(arrayelement.substr(arrayelement.length()-1,1)==scpRightBracket)
			{
				return FindArrayElement(arrayelement);
			}
			else
			{
				if(IsStaticNumber(arrayelement))
				{
					int Index = StringToInt(arrayelement.c_str());
					ScpObject * arrayobj = FindObject(arrayname);
					if(arrayobj)
					{
						if(arrayobj->GetType()==ObjArray)
						{
							ScpObject * childobj = ((ScpArrayObject *)arrayobj)->GetElement(Index);
							if(childobj)
							{
								return childobj;
							}
						}
					}
				}			
				else
				{
					ScpObject * arrayobj = FindObject(arrayname);
					if(arrayobj)
					{
						if(arrayobj->GetType()==ObjArray)
						{							
							ScpObject * childobj = ((ScpArrayObject *)arrayobj)->GetElement(arrayelement);
							if(childobj)
							{
								return childobj;
							}
							ScpObject * obj = FindObject(arrayelement);
							if(obj && obj->GetType()==ObjInt)
							{
								int Index =((ScpIntObject *)obj)->value;
								return ((ScpArrayObject *)arrayobj)->GetElement(Index);
							}
							else if (obj && obj->GetType() == ObjBigInt)
							{
								int Index = ((ScpBigIntObject *)obj)->value;
								return ((ScpArrayObject *)arrayobj)->GetElement(Index);
							}
							else
							{
								//Invalid Array Item Refrence
								
							}
						}
					}
				}
			}
		}
	}	
	return NULL;
}
ScpObject * ScpObjectSpace::FindLocalObject(const std::string& objname)
{
	ScpObject* temp =NULL;
	/*size_t pos1 = objname.rfind(scpRightBracket);
	if(pos1==(objname.length()-1))
	{
		temp=FindTableElement(objname);
		if(temp)
		{
			return temp;
		}
		temp = FindArrayElement(objname);
		if(temp)
		{
			return temp;
		}		
	}*/
	//temp = FindClassMemberVariable(objname);
	//if(temp)
	//{
	//	return temp;
	//}
	//temp = FindStructMemberVariable(objname);
	//if(temp)
	//{
	//	return temp;
	//}
	//temp = FindClassOrStructMemberVariable(objname);
	//if (temp)
	//{
	//	return temp;
	//}
	temp = userobject.GetObject(objname);
	return temp;
}
ScpObject * ScpObjectSpace::FindObject(IN const std::string& objname)
{
	ScpObject* temp =NULL;
	//size_t pos1 = objname.rfind(scpRightBracket);
	//if(pos1==(objname.length()-1))
	//{
	//	temp=FindTableElement(objname);
	//	if(temp)
	//	{
	//		return temp;
	//	}
	//	temp = FindArrayElement(objname);
	//	if(temp)
	//	{
	//		return temp;
	//	}		
	//}
	//temp = FindClassMemberVariable(objname);
	//if(temp)
	//{
	//	return temp;
	//}
	//temp = FindStructMemberVariable(objname);
	//if(temp)
	//{
	//	return temp;
	//}
	//temp = FindClassOrStructMemberVariable(objname);
	//if (temp)
	//{
	//	return temp;
	//}
	temp=userobject.GetObject(objname);
	if(temp)
	{			
		return temp;
	}
	else
	{
		if(parentspace)
		{
			return parentspace->FindObject(objname);
		}
		else
		{
			return NULL;
		}
	}		
}
ScpObject * ScpObjectSpace::FindGlobalObject(const std::string & objname)
{
	if (parentspace)
	{
		return parentspace->FindGlobalObject(objname);
	}
	else
	{
		return FindObject(objname);
	}
}
std::string ScpObjectSpace::GetObjectSpace(IN const std::string objname)
{
	ScpObject* temp=userobject.GetObject(objname);
	if(temp)
	{
		return spacename;
	}
	else
	{
		if(parentspace)
		{
			return parentspace->GetObjectSpace(objname);
		}
		else
		{
			return "";
		}
	}
}
BOOL ScpObjectSpace::AddObject(std::string strObjname,ScpObject *obj,std::string scope)
{
	if(ObjectSpaceType==Space_Class)
	{
		ScpClassObject * classObj =(ScpClassObject * )belongto;
		if(classObj)
		{
			classObj->memberattrmap[strObjname]=classObj->MemberVariableAttribute;
		}
	}
	//被映射的对象不能时临时对象
	obj->istemp = false;
	//if (obj->GetType() == ObjExpressionNode)
	//{
	//	if (obj->RefCount >=1)
	//	{
	//		obj->RefCount--;
	//	}
	//	//printf("node %S refcount %d %0x\n", strObjname.c_str(), obj->RefCount, obj);
	//}
	return userobject.MapObject(strObjname,obj,scope);
}
void ScpObjectSpace::EraseObject(std::string strObjname)
{
	userobject.UnMapObject(strObjname);
}
void ScpObjectSpace::EraseObject(ScpObject * Obj)
{
    std::string strObjname = userobject.GetObjectName(Obj);
	if (strObjname != "")
	{
		userobject.UnMapObject(strObjname);
	}
}
ScpObjectType ScpObjectSpace::GetType(std::string strObjname)
{
	ScpObject * temp = FindObject(strObjname);
	if(temp)
		return temp->GetType();
	else
		return ObjUnknown;
}
std::string ScpObjectSpace::GetObjectName(ScpObject * obj)
{
	return userobject.GetObjectName(obj);
}
std::string ScpObjectSpace::GetObjectNameR(ScpObject * obj)
{
	std::string name = userobject.GetObjectName(obj);
	if (name.empty())
	{
		ScpObjectSpace * pobjectSpace = parentspace;
		while (pobjectSpace)
		{
			name = pobjectSpace->GetObjectName(obj);
			if (!name.empty())
			{
				break;
			}
			pobjectSpace = pobjectSpace->parentspace;
		}
	}
	return name;
}
ScpObject * ScpObjectSpace::AcquireTempObject(ScpObjectType type)
{
	ScpObject * tmp = NULL;
	if (type == ObjInt)
	{
		tmp = AcquireTempObjectUni(UnusedTemp_Int_Objects);		
	}
	else if (type == ObjDouble)
	{
		tmp = AcquireTempObjectUni(UnusedTemp_Double_Objects);
	}
	else if (type == ObjBigInt)
	{
		tmp = AcquireTempObjectUni(UnusedTemp_BigInt_Objects);
	}
	else if (type == ObjString)
	{
		tmp = AcquireTempObjectUni(UnusedTemp_String_Objects);
	}
	else if (type ==  ObjExpressionNode)
	{
		tmp = AcquireTempObjectUni(UnusedTemp_ExpressionNode_Objects);
	}
	else
	{
		ITPOBJECTS it = UnusedTempObjects.begin();
		while (it != UnusedTempObjects.end())
		{
			tmp = *it;
			if (tmp->RefCount < 0)
			{
				it = UnusedTempObjects.erase(it);
				continue;
			}
			if (tmp->GetType() == type)
			{
				UnusedTempObjects.erase(it);
				tmp->istemp = true;
				tmp->AddRef();
				return tmp;
			}
			it++;
		}
	}
	if (!tmp)
	{
		tmp = BaseObjectFactory(type);
		tmp->istemp = true;
		tmp->AddRef();
	}	
	return tmp;
}
void ScpObjectSpace::ReleaseTempObject(ScpObject * tempobj)
{
	if (tempobj->istemp)
	{
		//std::wstring name = GetObjectName(tempobj);
		//if (!name.empty())
		//{
		//	//说明已经被映射到了对象名字空间，这里不能放进临时对象缓冲区
		//	return;
		//}
		if (tempobj->RefCount > 0)
		{
			tempobj->RefCount--;
		}
		if(tempobj->RefCount==0)
		{			
			if (tempobj->GetType() == ObjInt)
			{
				ReleaseTempObjectUni(tempobj, UnusedTemp_Int_Objects);
			}
			else if (tempobj->GetType() == ObjDouble)
			{
				ReleaseTempObjectUni(tempobj, UnusedTemp_Double_Objects);
			}
			else if (tempobj->GetType() == ObjBigInt)
			{
				ReleaseTempObjectUni(tempobj, UnusedTemp_BigInt_Objects);
			}
			else if (tempobj->GetType() == ObjString)
			{
				ReleaseTempObjectUni(tempobj, UnusedTemp_String_Objects);
			}
			else if (tempobj->GetType() == ObjExpressionNode)
			{
				ReleaseTempObjectUni(tempobj, UnusedTemp_ExpressionNode_Objects);
			}
			else
			{
				ITPOBJECTS result = find(UnusedTempObjects.begin(), UnusedTempObjects.end(), tempobj);
				if (result == UnusedTempObjects.end()) //没找到
				{					
					tempobj->RefCount = 0;
					//UnusedTempObjects.push_back(tempobj);
					UnusedTempObjects.insert(UnusedTempObjects.begin(), tempobj);

				}
			}			
		}		
	}
}
void ScpObjectSpace::DestroyTempObjects()
{	
	DestroyTempObjectsUni(UnusedTempObjects);
	DestroyTempObjectsUni(UnusedTemp_Int_Objects);	
	DestroyTempObjectsUni(UnusedTemp_Double_Objects);
	DestroyTempObjectsUni(UnusedTemp_BigInt_Objects);
	DestroyTempObjectsUni(UnusedTemp_String_Objects);
	DestroyTempObjectsUni(UnusedTemp_ExpressionNode_Objects);
}
ScpObject * ScpObjectSpace::AcquireTempObjectUni(VTPOBJECTS & TempObjects)
{
	ScpObject * tmp = NULL;
	ITPOBJECTS it = TempObjects.begin();
	while (it != TempObjects.end())
	{
		tmp = *it;
		if (tmp->RefCount < 0)
		{
			it = TempObjects.erase(it);
			continue;
		}
		else
		{
			TempObjects.erase(it);
			tmp->istemp = true;
			tmp->AddRef();
			return tmp;
		}
		it++;
	}
	return tmp;
}
void ScpObjectSpace::ReleaseTempObjectUni(ScpObject * tempobj, VTPOBJECTS & TempObjects)
{
	ITPOBJECTS result = find(TempObjects.begin(), TempObjects.end(), tempobj);
	if (result == TempObjects.end()) //没找到
	{		
		if (tempobj->GetType() == ObjInt)
		{
			((ScpIntObject *)tempobj)->value = 0;
		}
		else if (tempobj->GetType() == ObjDouble)
		{
			((ScpDoubleObject *)tempobj)->value = 0;
		}
		else if (tempobj->GetType() == ObjBigInt)
		{
			((ScpBigIntObject *)tempobj)->value = 0;
		}
		else if (tempobj->GetType() == ObjString)
		{
			((ScpStringObject *)tempobj)->Clear();
		}
		tempobj->RefCount = 0;
		TempObjects.insert(TempObjects.begin(), tempobj);
	}
}
void ScpObjectSpace::DestroyTempObjectsUni(VTPOBJECTS & TempObjects)
{
	ScpObject * tmp = NULL;
	ITPOBJECTS it = TempObjects.begin();
	while (it != TempObjects.end())
	{
		tmp = *it;
		tmp->DelRef();
		it++;
	}
}
BOOL ScpObjectSpace::IsMyParentSpace(ScpObjectSpace * space)
{
	BOOL bret = FALSE;
	ScpObjectSpace * pspace =this->parentspace;
	while(pspace!=NULL)
	{
		if(pspace==space)
		{
			bret = TRUE;
			break;
		}
		pspace=pspace->parentspace;
	}
	return bret;
}
//void ScpObjectSpace::AddTempObject(ScpObject * tempobj)
//{
//	if(tempobj->istemp)
//	{
//		ITPOBJECTS result = find( TempObjects.begin( ), TempObjects.end( ), tempobj ); 
//		if ( result == TempObjects.end( ) ) //没找到
//		{
//			tempobj->AddRef();
//			TempObjects.push_back(tempobj);
//		}
//	}
//	
//}
//void ScpObjectSpace::ClearTempObjects()
//{
//	ITPOBJECTS it = TempObjects.begin();	
//	while(it!=TempObjects.end())
//	{
//		ScpObject * tmp = *it;
//		if(tmp)
//			tmp->DelRef();
//		it = TempObjects.erase(it);
//	}
//}
std::string ScpObjectSpace::GetNewTempObjectName()
{
	std::string tempobjname ;
	do
	{
		//tempobjname = STDSTRINGEXT::Format("@@tempobj%d", ScpRandomNumberObject::GetRandom().value);
		//tempobjname = STDSTRINGEXT::Format("%s%d", LastTempObjectName.c_str(),++LastTempObjAppendix);
		tempobjname = LastTempObjectName + IntToString(++LastTempObjAppendix);
		//tempobjname = GenRandomString();
	}while (FindLocalObject(tempobjname));
	//LastTempObjectName = tempobjname;
	return tempobjname;
}

bool ScpObjectSpace::MoveToSpace(ScpObject * obj, ScpObjectSpace * space)
{
	if (obj && space)
	{
		if (space->AddObject(this->GetObjectName(obj), obj))
		{
			this->EraseObject(obj);
			return true;
		}		
	}
	return false;
}

ScpObjectSpace * ScpObjectSpace::GetGlobalSpace()
{
	ScpObjectSpace * g = this;
	while (g->parentspace)
	{
		g = g->parentspace;
	}
	if (g->ObjectSpaceType == Space_Global)
	{
		return g;
	}
	return nullptr;
}

ScpObjectSpace * ScpObjectSpace::FindObject_ObjectSpace(ScpObject * obj)
{
	std::string name = userobject.GetObjectName(obj);
	if (name.empty())
	{
		ScpObjectSpace * pobjectSpace = parentspace;
		while (pobjectSpace)
		{
			name = pobjectSpace->GetObjectName(obj);
			if (!name.empty())
			{
				return pobjectSpace;
			}
			pobjectSpace = pobjectSpace->parentspace;
		}
	}
	else
	{
		return this;
	}
	return nullptr;
}
