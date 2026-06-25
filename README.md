# ModuleAndPlugin 실습 - 적용 가이드

이 zip은 "필수 구현 기능" 체크리스트의 2~6번(코드/파일 부분)을 전부 만들어 둔 것입니다.
1번(새 프로젝트 생성)은 언리얼 에디터의 GUI 마법사로만 가능해서 직접 실행해주셔야 합니다.

────────────────────────────────────────
## 0단계 (수동, GUI) - 프로젝트 생성
────────────────────────────────────────
1. Unreal Engine 실행 → Games → Third Person → **C++** (Blueprint 아님!) → Scalable
2. 프로젝트 이름: `ModuleAndPlugin`
3. Create 클릭 → Visual Studio가 같이 열릴 때까지 대기
4. 생성되면 에디터/VS 모두 닫기 (파일 충돌 방지)

생성되면 프로젝트 루트에 다음이 이미 존재합니다:
```
ModuleAndPlugin/
├── ModuleAndPlugin.uproject
├── Source/
│   ├── ModuleAndPlugin/
│   │   ├── ModuleAndPlugin.Build.cs
│   │   ├── ModuleAndPlugin.h / .cpp
│   │   ├── ModuleAndPluginCharacter.h / .cpp   ← 우리가 손댈 파일
│   │   └── ... (GameMode 등)
│   ├── ModuleAndPlugin.Target.cs          ← 덮어쓰기
│   └── ModuleAndPluginEditor.Target.cs    ← 덮어쓰기
```

────────────────────────────────────────
## 1단계 - Test 모듈 복사 (체크리스트 2번)
────────────────────────────────────────
이 zip의 `Source/Test/` 폴더 전체를
프로젝트의 `Source/` 폴더 안에 그대로 복사합니다.

결과:
```
프로젝트Root/Source/Test/Test.Build.cs
프로젝트Root/Source/Test/Test.h
프로젝트Root/Source/Test/Test.cpp
프로젝트Root/Source/Test/TestActor.h
프로젝트Root/Source/Test/TestActor.cpp
```

────────────────────────────────────────
## 2단계 - Target.cs 교체 (체크리스트 3번 일부)
────────────────────────────────────────
이 zip의 `Targets/ModuleAndPlugin.Target.cs`,
`Targets/ModuleAndPluginEditor.Target.cs` 두 파일을
프로젝트의 `Source/` 폴더에 있는 동일한 이름 파일에 **덮어쓰기**합니다.
(ExtraModuleNames에 "Test"가 추가된 버전입니다)

────────────────────────────────────────
## 3단계 - .uproject 수정 (체크리스트 3번 일부)
────────────────────────────────────────
`ModuleAndPlugin.uproject.example.json` 파일을 참고해서
**본인 프로젝트의 실제 .uproject 파일을 직접 텍스트 편집기로 열어** 다음 두 가지만 추가하세요.
(예시 파일을 그대로 덮어쓰지 마세요 - 본인 프로젝트엔 이미 다른 플러그인 항목들이 있을 수 있습니다)

`Modules` 배열에 추가:
```json
{
	"Name": "Test",
	"Type": "Runtime",
	"LoadingPhase": "PreDefault"
}
```

`Plugins` 배열에 추가 (없으면 "Plugins": [...] 자체를 새로 만들면 됩니다):
```json
{
	"Name": "Temporary",
	"Enabled": true
}
```

────────────────────────────────────────
## 4단계 - 주 게임 모듈 수정 (체크리스트 4번)
────────────────────────────────────────
`PrimaryModule_Snippets/` 폴더의 3개 안내 파일을 보고 직접 적용하세요.
1. `01_ModuleAndPlugin_Build_cs_변경사항.txt`
   → ModuleAndPlugin.Build.cs 에 Test를 Private 의존성으로 추가
2. `02_Character_h_변경사항.txt`
   → ModuleAndPluginCharacter.h 에 SpawnTestModuleActor() 함수 선언 추가
3. `03_Character_cpp_변경사항.txt`
   → ModuleAndPluginCharacter.cpp 에 #include "TestActor.h" + 함수 구현 추가

────────────────────────────────────────
## 5단계 - Temporary 플러그인 복사 (체크리스트 5번)
────────────────────────────────────────
이 zip의 `Plugins/Temporary/` 폴더 전체를
프로젝트의 `Plugins/` 폴더 안에 그대로 복사합니다.
(프로젝트 루트에 Plugins 폴더가 없으면 새로 만들면 됩니다)

결과:
```
프로젝트Root/Plugins/Temporary/Temporary.uplugin
프로젝트Root/Plugins/Temporary/Content/            (빈 폴더, 콘텐츠 브라우저 표시용)
프로젝트Root/Plugins/Temporary/Source/Temporary/Temporary.Build.cs
프로젝트Root/Plugins/Temporary/Source/Temporary/Temporary.h
프로젝트Root/Plugins/Temporary/Source/Temporary/Temporary.cpp
```
3단계에서 .uproject의 Plugins 배열에 "Temporary": Enabled true 를 이미 추가했으면
이 플러그인은 자동으로 활성화된 상태로 인식됩니다.

────────────────────────────────────────
## 6단계 (수동, GUI/VS) - 빌드 & 검증 (체크리스트 3, 6번)
────────────────────────────────────────
1. `ModuleAndPlugin.uproject` 우클릭 → **Generate Visual Studio project files**
2. `.sln` 열고 Development Editor / Win64 구성으로 빌드 (Ctrl+Shift+B)
   - 빌드가 안 되면 보통 원인:
     a) Build.cs 내 클래스 이름이 모듈 폴더명과 정확히 일치하지 않음 (Test ↔ Test.Build.cs)
     b) .uproject의 LoadingPhase 오타 (PreDefault 정확히)
     c) TestActor.h의 `TEST_API` 매크로명이 모듈명(Test)과 안 맞을 때
        → 모듈명이 다르면 PROJECT_API 형태가 아니라 항상 "모듈명_API" (대문자) 형태여야 합니다.
3. 빌드 성공 후 에디터 실행
4. **콘텐츠 브라우저**에서 좌측 트리/필터에 "Temporary" 플러그인 폴더가 보이는지 확인
   (보이지 않으면 콘텐츠 브라우저 옵션(설정 아이콘) → "Show Plugin Content" 체크)
5. PIE(Play) 실행 → 화면에 다음 두 메시지가 같이 뜨면 정상:
   - 초록색: "TestActor::BeginPlay - Test 모듈 동작 확인!"  (Test 모듈 단독 동작 증거)
   - 청록색: "Character::BeginPlay -> Test 모듈의 TestActor 스폰 성공!"  (모듈 간 상호작용 증거)
6. Output Log 창에서도 `[TestActor] BeginPlay 호출됨...` 로그가 찍히는지 확인

────────────────────────────────────────
## 핵심 개념 정리 (과제 요약과 매칭)
────────────────────────────────────────
- Public Dependency Module: 헤더(.h)에서도 쓰는 모듈 → 이 모듈을 쓰는 "남"의 헤더에도 영향
- Private Dependency Module: .cpp에서만 쓰는 모듈 → 이 모듈을 쓰는 "남"에게는 안 보임
  → ModuleAndPlugin → Test 의존성이 Private인 이유: Character.h가 아니라 .cpp에서만 include하기 때문
- 모듈(Module): 같은 프로젝트 안에서 컴파일 단위를 나누는 것 (Source/ 안에 위치, 배포 단위는 아님)
- 플러그인(Plugin): 모듈(들) + 콘텐츠 + 메타데이터(.uplugin)를 묶어 재사용/배포 가능한 단위
- LoadingPhase "PreDefault": 게임의 기본(Default) 모듈들이 로드되기 *전에* 먼저 로드됨
  (Test 모듈을 다른 기본 모듈보다 먼저 준비시키고 싶을 때 사용)
