using UnrealBuildTool;
using System.Collections.Generic;

public class ModuleAndPluginTarget : TargetRules
{
	public ModuleAndPluginTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		// 기본으로 생성된 "ModuleAndPlugin" 옆에 새로 만든 "Test" 모듈을
		// 빌드 대상에 등록해야 컴파일 시 함께 빌드됩니다.
		ExtraModuleNames.AddRange(new string[] { "ModuleAndPlugin", "Test" });
	}
}
