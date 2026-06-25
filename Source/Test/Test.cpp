#include "Test.h"
#include "Modules/ModuleManager.h"

// 일반(범용) 모듈이므로 별도의 StartupModule/ShutdownModule 구현 없이
// 엔진이 제공하는 FDefaultModuleImpl을 그대로 사용합니다.
IMPLEMENT_MODULE(FDefaultModuleImpl, Test);
