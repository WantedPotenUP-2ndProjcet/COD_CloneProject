# Fixing

## 기준

- **수정전 상태**: 최근 `StoryManager` 프리뷰 안정화 수정 직전 상태
- **수정후 상태**: 최근 `StoryManager` 프리뷰 안정화 수정이 반영되었던 상태
- 이 문서는 전체 코드 보관본이 아니라 **수정전/수정후 차이점만 기록**한다.

## 차이 기록

### 1. `Source/COD/Public/StoryManager.h`

수정전에는 `OnConstruction`, `BeginPlay`, `Tick`, `PostEditChangeProperty` 중심의 프리뷰 구조만 있었고, 에디터 선택 변경을 직접 다루는 선언은 없었다.

수정후에는 아래 선언이 추가되었다.

- `virtual void PostRegisterAllComponents() override;`
- `virtual void PostUnregisterAllComponents() override;`

에디터 선택 변경 대응용 private 함수가 추가되었다.

- `RegisterEditorSelectionDelegates()`
- `UnregisterEditorSelectionDelegates()`
- `OnEditorSelectionChanged(UObject* SelectionObject)`

에디터 선택 이벤트 바인딩 상태를 저장하는 멤버가 추가되었다.

- `FDelegateHandle SelectionChangedHandle`

정리하면, 헤더 차이는 **에디터 selection delegate 기반 복구 흐름을 수용하기 위한 선언/상태 추가**였다.

### 2. `Source/COD/Private/StoryManager.cpp`

#### 2-1. include 차이

수정후에는 에디터 selection event 연결을 위해 아래 include가 추가되었다.

- `#include "Selection.h"` under `#if WITH_EDITOR`

#### 2-2. 컴포넌트 라이프사이클 차이

수정전에는 `OnConstruction()` 이후 별도 등록/해제 훅이 없었다.

수정후에는 아래 함수가 추가되었다.

- `PostRegisterAllComponents()`
- `PostUnregisterAllComponents()`

이 추가 함수에서 수행하려던 역할은 다음과 같다.

- 컴포넌트 등록 시 selection delegate 바인딩
- 컴포넌트 해제 시 selection delegate 해제
- unregister 시 preview spline 정리

#### 2-3. 스플라인 생성 방식 차이

수정전 프리뷰 spline 생성 흐름은 아래와 같았다.

1. `NewObject<USplineComponent>()`
2. `AddInstanceComponent()`
3. `RegisterComponent()`
4. `for (...) { AddSplinePoint(...) }`
5. `SetSplinePointType(..., Linear, false)`
6. `UpdateSpline()`

수정후 프리뷰 spline 생성 흐름은 아래처럼 바뀌었다.

1. `NewObject<USplineComponent>()`
2. `ClearSplinePoints(false)`
3. `TArray<FVector> PreviewPoints` 생성
4. NavPath 점들을 `PreviewPoints`에 누적
5. `SetSplinePoints(PreviewPoints, ESplineCoordinateSpace::World, false)`
6. `SetSplinePointType(..., Linear, false)`
7. `AddInstanceComponent()`
8. `RegisterComponent()`
9. `UpdateSpline()`

즉, 핵심 차이는 다음 두 가지였다.

- `AddSplinePoint()` 누적 방식에서 `SetSplinePoints()` 전체 세팅 방식으로 변경
- 기본 spline point 제거를 위해 `ClearSplinePoints(false)` 호출 추가

#### 2-4. 에디터 선택 이벤트 처리 차이

수정전에는 preview 표시/제거 판단이 사실상 아래 경로에만 묶여 있었다.

- `OnConstruction()`
- `Tick()`
- `PostEditChangeProperty()`

수정후에는 아래 함수가 새로 추가되었다.

- `RegisterEditorSelectionDelegates()`
- `UnregisterEditorSelectionDelegates()`
- `OnEditorSelectionChanged(UObject* SelectionObject)`

그리고 `USelection::SelectionChangedEvent.AddUObject(...)` 바인딩이 들어갔다.

즉, 선택 상태 변화에 대해 **폴링 보조 + selection event 직접 반응** 구조로 바꾸려 했던 수정이다.

### 3. `Source/COD/COD.Build.cs`

수정전에는 `NavigationSystem`까지만 의존성이 있었고, 에디터 전용 모듈 추가는 없었다.

수정후에는 아래 조건부 의존성이 추가되었다.

```csharp
if (Target.bBuildEditor)
{
    PrivateDependencyModuleNames.Add("UnrealEd");
}
```

이 차이는 `Selection.h`, `USelection::SelectionChangedEvent` 사용을 위한 **에디터 전용 모듈 의존성 추가**에 해당한다.

## 한 줄 요약

이번 수정의 본질은 아래 두 축이었다.

1. **Spline 생성 방식을 `AddSplinePoint` 누적형에서 `ClearSplinePoints + SetSplinePoints`형으로 변경**
2. **Preview 복구를 위해 `Tick` 의존 구조에 `USelection::SelectionChangedEvent` 기반 selection 대응을 추가**
