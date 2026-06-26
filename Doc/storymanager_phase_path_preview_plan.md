# StoryManager Phase Path Preview 개발 계획

## 목적

현재 `StoryManager`는 **런타임에서 Phase 변경 명령을 전달하는 역할**에 가깝다.

이번 작업의 목표는 여기에 **에디터에서 미리 Ally 이동 동선을 보는 프리뷰 기능**을 추가하는 것이다.

핵심 요구는 아래와 같다.

- 레벨에 배치된 `AAllyCharacterBase`들을 관리할 수 있어야 한다.
- 선택된 `StoryManager`가 현재 레벨 위에 Ally들의 예상 이동 경로를 그릴 수 있어야 한다.
- 프리뷰는 **기존 런타임 로직을 크게 건드리지 않는 방향**으로 추가되어야 한다.

## 기본 설계 방향

처음부터 새 `Manager` Actor를 만든다고 가정하면 흐름은 아래와 같다.

1. 레벨에 `Manager` Actor를 배치한다.

2. `Manager`는 레벨에 배치된 `AAllyCharacterBase`들을 수집한다.

3. `Manager`는 현재 `PreviewPhase` 기준으로 각 Ally의 목표 지점을 구한다.

4. `Manager`는 `현재 위치 -> 목표 위치` 경로를 계산한다.

5. 계산된 경로 점들을 이용해 **스플라인 또는 선형 프리뷰 그래픽**을 그린다.

6. `Manager`가 선택된 상태에서만 프리뷰를 갱신하고, 필요 시 숨긴다.

이 흐름을 그대로 **기존 `StoryManager`에 기능 추가 형태로 붙이는 것**이 이번 계획의 핵심이다.

## 왜 기존 구조를 전부 바꾸지 않는가

현재 `StoryManager`에는 이미 런타임용 `AllyControllers` 배열이 있고, `ChangePhase()`는 실제 Phase 진행 로직에 연결되어 있다.

이 구조를 지금 바로 `AAllyCharacterBase` 중심으로 전면 교체하면, 프리뷰 기능 하나 추가하는 작업에 비해 변경 범위가 불필요하게 커진다.

따라서 이번 방향은 아래와 같이 잡는다.

- 기존 `AllyControllers`는 유지한다.
- 새로 `RegisteredAllies` 배열을 추가한다.
- `RegisteredAllies`는 **에디터 프리뷰 전용 관리 목록**으로 사용한다.
- 기존 Phase 명령 전달 로직과 프리뷰 로직은 분리한다.

즉, 이번 작업은 **구조 교체가 아니라 기능 확장**이다.

## 현재 코드 기준 해석

현재 구조는 아래처럼 나뉘어 있다.

- `AStoryManager`
  - Phase 변경
  - `AAllyAIController` 등록
  - 등록된 Controller에 명령 전달

- `AAllyAIController`
  - `RecieveOrder()` 호출 시 실제 이동 명령 수행
  - `MoveToLocation()`으로 목적지 이동

- `AAllyCharacterBase`
  - `FirstDefensePoint`
  - `SecondDefensePoint`
  - `DefenseAcceptanceRadius`

즉, **실제 목적지 데이터는 이미 `AAllyCharacterBase` 쪽에 있다.**

따라서 프리뷰도 `AIController`를 기준으로 보지 말고, **`AAllyCharacterBase` + 목적지 Actor** 조합으로 계산하는 편이 자연스럽다.

## 개발 원칙

- 기존 런타임 Phase 진행 로직은 최대한 유지한다.
- 프리뷰 기능은 에디터 전용 흐름으로 분리한다.
- 경로 표시용 데이터는 `AAllyCharacterBase` 기준으로 읽는다.
- 첫 구현은 단순하게 간다.
  - 1차는 선형 경로 또는 간단한 스플라인
  - 2차에서 화살표 메시, 색상 구분, 고급 연출 추가

## 1차 구현 목표

1차 목표는 아래만 달성하면 된다.

- `StoryManager`가 레벨 내 `AAllyCharacterBase`를 수집할 수 있다.
- `PreviewPhase`를 바꾸면 각 Ally의 목적지를 해석할 수 있다.
- `StoryManager` 선택 시 해당 Ally들의 경로가 레벨에 그려진다.
- 기존 `ChangePhase()` / `RecieveOrder()` / `MoveToLocation()` 런타임 흐름은 그대로 유지된다.

## StoryManager에 추가할 개념

### 1. Ally 프리뷰 관리용 배열

추가 대상:

- `TArray<TWeakObjectPtr<AAllyCharacterBase>> RegisteredAllies`

역할:

- 에디터 프리뷰를 그릴 때 참조하는 Ally 목록

주의:

- 이 배열은 기존 `AllyControllers`를 대체하지 않는다.
- 프리뷰용 목록으로만 사용한다.

### 2. 프리뷰 설정값

추가 후보:

- `bool bShowPhasePreview`
- `EPhase PreviewPhase`
- `bool bAutoCollectAllies`

역할:

- 프리뷰 On/Off
- 어떤 Phase 기준으로 그릴지 선택
- Ally를 자동 수집할지 여부 결정

### 3. 프리뷰 결과 보관용 컴포넌트

추가 후보:

- `TArray<TObjectPtr<USplineComponent>> PreviewSplineComponents`

역할:

- Ally별로 생성된 경로 스플라인을 보관
- 갱신 전에 제거하고 다시 생성하는 방식으로 사용

## Ally 수집 방식

### 권장 방식: StoryManager가 자동 탐색

기본 방식은 아래가 좋다.

- `OnConstruction()` 또는 에디터 갱신 시점에 레벨의 `AAllyCharacterBase`를 다시 탐색
- `RegisteredAllies`를 재구성

장점:

- 에디터에서 배치/삭제/복제 후에도 동기화가 쉽다.
- 수동 등록 누락 가능성이 적다.
- 현재 목적에 가장 단순하다.

### 보조 방식: Ally가 Manager에 등록

추가로 아래 함수를 둘 수 있다.

- `RegisterAlly(AAllyCharacterBase* Ally)`
- `UnregisterAlly(AAllyCharacterBase* Ally)`

이 방식은 런타임이나 명시적 연결에는 유용하지만, 이번 기능의 메인 수집 방식으로 삼기보다는 **보조 수단**으로 두는 편이 안전하다.

## Phase별 목표 지점 해석

현재 구조를 기준으로 하면 1차 해석 규칙은 단순하다.

- `EPhase::Phase1` -> `FirstDefensePoint`
- `EPhase::Phase2` -> `SecondDefensePoint`

이 로직은 `StoryManager` 내부 헬퍼 함수나 `AAllyCharacterBase`의 조회 함수로 분리하는 것이 좋다.

예시 역할:

- `AActor* GetPreviewTargetForPhase(AAllyCharacterBase* Ally, EPhase Phase)`

장점:

- 프리뷰와 런타임 이동 목적지 규칙을 같은 기준으로 맞출 수 있다.
- 나중에 `Phase3`, `CoverPoint`, `FallbackPoint`가 늘어나도 확장하기 쉽다.

## 경로 계산 방식

1차 구현은 **NavPath 계산 결과를 화면에 그리는 방식**으로 간다.

흐름:

1. Ally의 현재 위치를 구한다.

2. `PreviewPhase`에 해당하는 목표 Actor 위치를 구한다.

3. Navigation System으로 경로 점 목록을 계산한다.

4. 경로 점들을 기반으로 스플라인 또는 선을 만든다.

중요한 점:

- 스플라인은 **보여주는 방식**이다.
- 실제 경로 계산 기준은 **NavPath 점 목록**이다.

따라서 처음부터 과하게 곡선을 부드럽게 만들기보다, **실제 이동 경로와 가깝게 보이는 선형 표현**부터 시작하는 편이 안전하다.

## 프리뷰 드로우 방식

1차는 아래 우선순위로 구현한다.

1. `USplineComponent` 생성

2. 경로 점 추가

3. `SetClosedLoop(false)` 유지

4. 디버그 드로우 또는 스플라인 시각화로 확인

추가 고려:

- 점마다 약간의 `Z Offset`을 줘서 바닥과 겹쳐 깜빡이는 문제를 줄인다.
- Ally마다 색상을 다르게 주거나, Phase별 색상 규칙을 줄 수 있다.

## 에디터 갱신 시점

프리뷰 갱신 타이밍은 아래 순서로 고려한다.

### 1차 권장

- `OnConstruction()`
- `PostEditChangeProperty()`

적용 이유:

- `PreviewPhase` 변경 시 바로 갱신 가능
- 레벨에서 위치 이동 후 바로 반영 가능

### 추가 고려

- 선택된 상태에서만 갱신
- 선택 해제 시 프리뷰 제거

이 부분은 1차에서 완전히 자동화하지 못해도 된다.

우선은 **설정 변경 시 재생성되는 정도**만 되어도 개발자 사용성은 충분하다.

## StoryManager 개조 단계

### Step 1. 프리뷰용 Ally 배열 추가

목표:

- `RegisteredAllies` 추가
- 기존 `AllyControllers`는 유지

이 단계에서는 기존 런타임 로직을 건드리지 않는다.

### Step 2. Ally 자동 수집 함수 추가

추가 대상 예시:

- `CollectAlliesInLevel()`

역할:

- 레벨에 존재하는 `AAllyCharacterBase` 탐색
- `RegisteredAllies` 재구성

### Step 3. Phase별 목표 조회 함수 추가

추가 대상 예시:

- `GetPreviewTargetForPhase()`

역할:

- 특정 Ally가 현재 PreviewPhase에서 어디로 가야 하는지 계산

### Step 4. 프리뷰 경로 재생성 함수 추가

추가 대상 예시:

- `RebuildPhasePreview()`
- `ClearPhasePreview()`

역할:

- 기존 스플라인 제거
- Ally별 경로 계산
- 새 스플라인 생성

### Step 5. 에디터 이벤트 연결

추가 대상 예시:

- `OnConstruction()`
- `PostEditChangeProperty()`

역할:

- 프리뷰 옵션 변경 시 자동 갱신

### Step 6. 런타임 이동 규칙과 프리뷰 규칙 정리

현재는 `AAllyAIController::MoveDefenseLocation()` 안에서 직접 `FirstDefensePoint`, `SecondDefensePoint`를 본다.

나중에는 아래처럼 정리하는 편이 좋다.

- 목적지 조회 규칙을 공용 함수로 모은다.
- 프리뷰와 실제 이동이 같은 기준을 쓰게 만든다.

단, 이 단계는 1차 구현 필수는 아니다.

## 작업 범위 제안

### 1차 작업 범위

- `StoryManager`에 프리뷰용 Ally 배열 추가
- Ally 자동 수집 구현
- `PreviewPhase` 추가
- `Phase1`, `Phase2` 기준 목적지 해석 구현
- 경로 스플라인 생성/삭제 구현
- `Doc` 문서화

### 2차 작업 범위

- 선택 상태일 때만 프리뷰 보이기
- Ally별 색상 구분
- 화살표 메시 또는 나이아가라 표시
- 경로 라벨 표시

### 3차 작업 범위

- `StoryManager`와 `AAllyAIController`의 목적지 해석 로직 공통화
- 신규 Phase 확장
- 컷신/연출 전용 이동 규칙 지원

## 리스크와 대응

### 리스크 1. 에디터에서 Ally 목록이 꼬일 수 있음

대응:

- 수동 등록만 믿지 말고 자동 탐색을 기본으로 둔다.

### 리스크 2. 스플라인이 실제 NavPath와 다르게 보여질 수 있음

대응:

- 1차는 선형 표현을 우선한다.
- 필요 시 스플라인 포인트 타입을 조절한다.

### 리스크 3. 프리뷰 로직이 런타임 로직과 따로 놀 수 있음

대응:

- 목적지 해석 규칙을 한 곳으로 모으는 2차 정리를 계획한다.

## 결론

이번 기능은 **`StoryManager`를 새 구조로 갈아엎는 작업이 아니다.**

가장 현실적인 방향은 아래와 같다.

- 기존 `AllyControllers`는 유지한다.
- `RegisteredAllies`를 추가한다.
- `StoryManager`에 에디터 프리뷰 기능을 덧붙인다.
- 프리뷰는 `AAllyCharacterBase`의 목적지 데이터를 기준으로 그린다.

즉, 이번 작업의 성격은 **기존 Story 시스템 위에 Phase 이동 경로 프리뷰를 증분 추가하는 것**이다.
