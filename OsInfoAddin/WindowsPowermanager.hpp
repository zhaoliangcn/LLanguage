#include <PowrProf.h>
#pragma comment (lib,"PowrProf.lib")

void SuspendComputer()
{
	SetSuspendState(TRUE,TRUE,TRUE);
}