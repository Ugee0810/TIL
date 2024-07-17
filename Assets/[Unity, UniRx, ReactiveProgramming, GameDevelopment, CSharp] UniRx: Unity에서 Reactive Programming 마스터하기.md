# 2024-07-17
**Tags**: `Unity`, `UniRx`, `ReactiveProgramming`, `GameDevelopment`, `CSharp`

## What I Learned
UniRx: Unity에서 Reactive Programming 마스터하기

### 1. UniRx 라이브러리 개요
UniRx는 Unity를 위한 반응형 확장 라이브러리입니다. Rx(Reactive Extensions)의 아이디어를 Unity에 적용하여 게임 개발자들이 데이터 스트림과 이벤트 처리를 보다 효율적으로 관리할 수 있도록 도와줍니다. 이를 통해 비동기 작업과 이벤트 기반 프로그래밍이 간편해지고, 코드의 가독성과 유지보수성이 크게 향상됩니다.

### 2. UniRx의 ReactiveProperty와 ReactiveCommand 개념
#### ReactiveProperty
ReactiveProperty는 UniRx에서 제공하는 특수한 타입으로, 데이터의 변화를 감지하고 이에 반응하는 속성입니다. 이는 Observable을 확장한 것으로, 값의 변경을 실시간으로 감지하고 구독자들에게 알리는 역할을 합니다.

1. **ReactiveProperty 정의**: ReactiveProperty가 생성되고 초기 값이 설정됩니다.
2. **구독자 등록**: ReactiveProperty의 값 변화를 감지할 구독자가 등록됩니다.
3. **상태 변화**: ReactiveProperty의 값이 변경됩니다.
4. **구독자 알림**: 값 변경이 감지되면 등록된 구독자에게 알림이 전송됩니다.

#### ReactiveCommand
ReactiveCommand는 명령의 실행과 그 결과를 관리하는데 사용되는 UniRx의 타입입니다. 주로 버튼 클릭과 같은 사용자 입력을 처리하는데 사용되며, 명령의 실행 가능 여부와 결과를 Observable로 관리할 수 있습니다.

1. **ReactiveCommand 정의**: ReactiveCommand가 생성됩니다.
2. **명령 실행 조건 정의**: 명령이 실행될 조건을 설정합니다.
3. **구독자 등록**: 명령 실행 결과를 처리할 구독자를 등록합니다.
4. **명령 실행**: 특정 조건이 만족되면 명령이 실행됩니다.
5. **구독자 알림**: 명령 실행 결과가 구독자에게 전달됩니다.

### 3. ReactiveProperty 과도 사용의 단점 및 ReactiveCommand의 대체 장점
#### 과도한 ReactiveProperty 사용의 단점
- **메모리 누수**: ReactiveProperty는 구독(subscribe) 메커니즘을 통해 값의 변화를 감지하고 반응합니다. 하지만 구독을 해제(unsubscribe)하지 않으면 메모리 누수가 발생할 수 있습니다. 특히, Unity에서는 게임 오브젝트가 파괴될 때 구독을 명시적으로 해제하지 않으면 메모리 누수의 원인이 됩니다.
- **복잡한 디버깅**: ReactiveProperty를 통해 상태 변화를 관리하다 보면 여러 개의 ReactiveProperty가 서로 영향을 주고받게 됩니다. 이로 인해 어떤 상태 변화가 어디서 발생했는지 추적하기 어려워지고, 복잡한 디버깅 작업을 필요로 합니다. 특히, 다양한 상태가 얽혀 있을 경우 디버깅이 더욱 어려워집니다.
- **퍼포먼스 저하**: ReactiveProperty는 값이 변경될 때마다 모든 구독자에게 알림을 보내기 때문에, 빈번한 상태 변화가 발생할 경우 성능 저하가 발생할 수 있습니다. 특히, 대규모 게임 프로젝트에서는 수백 개 이상의 ReactiveProperty가 동시에 동작할 수 있어 퍼포먼스 이슈가 심각해질 수 있습니다.

#### ReactiveCommand의 대체 장점
- **명령 중심 설계**: ReactiveCommand는 명령 중심(command-oriented)으로 설계되어 특정 이벤트를 처리합니다. 이러한 구조는 로직이 명확히 분리되어 있어 유지보수성이 높아집니다. 예를 들어, 버튼 클릭 이벤트와 같은 명확한 사용자 액션에 반응할 때 유용합니다.
- **조건부 실행**: ReactiveCommand는 특정 조건이 만족될 때만 실행될 수 있도록 설계할 수 있습니다. 예를 들어, 플레이어가 특정 아이템을 소지하고 있을 때만 공격 명령을 실행하도록 할 수 있습니다. 이는 불필요한 명령 실행을 방지하고 성능을 최적화하는 데 도움을 줍니다.
- **코드 가독성**: 명령 중심의 ReactiveCommand는 코드 가독성을 높여줍니다. 이벤트 처리 로직이 명령 단위로 분리되어 있어 협업 시에도 각 명령의 역할과 동작을 쉽게 이해할 수 있습니다.

### 4. ReactiveProperty와 ReactiveCommand의 활용 사례 및 예제
#### ReactiveCommand를 사용하지 않고 ReactiveProperty만을 사용한 사례
```cs
using UnityEngine;
using UnityEngine.UI;
using UniRx;

public class ButtonHandler : MonoBehaviour
{
    [SerializeField] private Button button;
    
    public ReactiveProperty<bool> IsButtonClicked { get; private set; } = new();

    private void Start()
    {
        // 버튼 클릭 시 ReactiveProperty 값 변경
        button
            .OnClickAsObservable()
            .Subscribe(delegate { OnClickButton(); })
            .AddTo(this);

        // 값 변화 시 반응
        IsButtonClicked
            .AsObservable()
            .Subscribe(IsButtonClickedHandler)
            .AddTo(this);
    }

    private void OnClickButton()
    {
        IsButtonClicked.Value = true;
    }

    private void IsButtonClickedHandler(bool isButtonClicked)
    {
        if (isButtonClicked)
        {
            Debug.Log("Button Clicked!");
            IsButtonClicked.Value = false; // 상태 초기화
        }
    }
}
```

#### ReactiveProperty와 ReactiveCommand를 결합한 사례
```cs
using UnityEngine;
using UnityEngine.UI;
using UniRx;

public class ButtonHandler : MonoBehaviour
{
    [SerializeField] private Button button;

    public ReactiveCommand OnClickButtonCommand { get; private set; } = new();
    public ReactiveProperty<bool> IsButtonEnabled { get; private set; } = new();

    private void Start()
    {
        // 버튼 클릭 시 명령 실행
        button
            .OnClickAsObservable()
            .Subscribe(delegate { OnClickButton(); })
            .AddTo(this);

        // 명령 실행 시 반응
        OnClickButtonCommand
            .Subscribe(delegate { OnClickButtonExecuted(); })
            .AddTo(this);

        // ReactiveProperty와 버튼의 상호작용
        IsButtonEnabled
            .AsObservable()
            .Subscribe(IsButtonEnabledHandler)
            .AddTo(this);
    }

    private void OnClickButton()
    {
        OnClickButtonCommand.Execute();
    }

    private void OnClickButtonExecuted()
    {
        Debug.Log("ButtonHandler.OnClickButtonExecuted(): Entered");
        IsButtonEnabled.Value = !IsButtonEnabled.Value; // 상태 값 토글
    }

    private void IsButtonEnabledHandler(bool isEnabled)
    {
        button.interactable = isEnabled;
    }
}
```

### 5. 결론
UniRx를 활용하면 Unity에서의 반응형 프로그래밍이 훨씬 간편해집니다. ReactiveProperty와 ReactiveCommand를 적절히 사용하면 코드의 가독성과 유지보수성을 높일 수 있으며, 효율적인 데이터 처리가 가능합니다.
