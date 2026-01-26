# 2024-07-11
**Tags**: `programming`, `unity`, `dots`

## What I Learned
### 서론
Unity는 게임 개발자들 사이에서 가장 인기 있는 게임 엔진 중 하나로, 다양한 프로젝트에 적합한 여러 가지 패러다임을 제공합니다. 그러나 Unity에서 가장 적절한 패러다임은 무엇일까요? 이번 포스팅에서는 객체 지향, 컴포넌트 기반, 데이터 지향 패러다임을 비교 분석하고, 각 패러다임의 장단점 및 사용 예시를 통해 가장 적절한 패러다임을 도출해보겠습니다.

### 객체 지향 프로그래밍 (Object-Oriented Programming, OOP)
객체 지향 프로그래밍은 Unity의 기본적인 접근 방식입니다. 이는 게임 개발자들이 클래스를 사용하여 게임 오브젝트를 정의하고, 이 클래스의 인스턴스를 통해 게임을 구성하는 방식입니다.

#### 장점
- **재사용성**
  클래스와 객체는 재사용이 가능하여, 코드의 중복을 줄일 수 있습니다.
- **캡슐화**
  데이터와 함수를 객체 내에 캡슐화하여, 코드의 가독성과 유지보수성을 높일 수 있습니다.
- **상속**
  부모 클래스를 상속받아 새로운 클래스를 생성할 수 있어, 기능 확장이 용이합니다.

#### 예시 코드
```cs
public class Player : MonoBehaviour
{
    public float speed = 5f;
    public int health = 100;

    void Update()
    {
        Move();
    }

    void Move()
    {
        float move = Input.GetAxis("Horizontal") * speed * Time.deltaTime;
        transform.Translate(move, 0, 0);
    }
}
```

#### 상속이 유니티 시스템적으로 더 코드 관리에 불편함은 없을까?
상속은 강력한 기능을 제공하지만, Unity에서는 종종 상속보다 컴포넌트 기반 접근 방식이 더 적합할 수 있습니다. 이는 상속이 다음과 같은 문제를 야기할 수 있기 때문입니다:

- **복잡한 계층 구조**
  상속 계층이 깊어질수록 코드를 이해하고 유지보수하기 어려워집니다.
- **다중 상속 불가**
  C#은 다중 상속을 지원하지 않으므로, 여러 클래스로부터 상속받아야 하는 경우 문제가 발생할 수 있습니다.
- **의존성 증가**
  상속 관계가 많아질수록 클래스 간의 의존성이 증가하여, 코드 수정 시 영향 범위가 넓어질 수 있습니다.

이러한 이유로 Unity에서는 컴포넌트 기반 접근 방식을 선호하는 경우가 많습니다. 이는 각 기능을 독립된 컴포넌트로 나누어, 더 유연하고 관리하기 쉽게 합니다.

### 컴포넌트 기반 프로그래밍 (Component-Based Programming)
Unity의 핵심 개념인 컴포넌트 기반 프로그래밍은 OOP의 단점을 보완하는 패러다임입니다. 게임 오브젝트는 여러 컴포넌트로 구성되며, 각 컴포넌트는 특정 기능을 담당합니다.

#### 장점
- **유연성**
  서로 다른 기능을 가진 컴포넌트를 조합하여 다양한 오브젝트를 생성할 수 있습니다.
- **모듈화**
  기능별로 컴포넌트를 나누어 관리할 수 있어, 코드의 유지보수성이 높아집니다.
- **재사용성**
  컴포넌트를 재사용하여, 코드 중복을 줄일 수 있습니다.

#### 예시 코드 및 튜토리얼
1. 플레이어 이동 컴포넌트
```cs
public class PlayerMovement : MonoBehaviour
{
    public float speed = 5f;

    void Update()
    {
        Move();
    }

    void Move()
    {
        float move = Input.GetAxis("Horizontal") * speed * Time.deltaTime;
        transform.Translate(move, 0, 0);
    }
}
```

2. 플레이어 건강 컴포넌트
```cs
public class PlayerHealth : MonoBehaviour
{
    public int health = 100;

    void TakeDamage(int damage)
    {
        health -= damage;
        if (health <= 0)
        {
            Die();
        }
    }

    void Die()
    {
        // 플레이어 사망 로직
        Debug.Log("Player Died");
    }
}
```

3. Unity에서 컴포넌트 추가하기
위 두 컴포넌트를 작성한 후, Unity 에디터에서 GameObject에 추가하는 방법

- PlayerMovement 컴포넌트 추가
  1. Unity 에디터에서 빈 GameObject를 생성합니다.
  2. 해당 GameObject를 선택한 상태에서 "Add Component" 버튼을 클릭합니다.
  3. PlayerMovement 스크립트를 선택하여 추가합니다.
- PlayerHealth 컴포넌트 추가
  1. 동일한 GameObject에 "Add Component" 버튼을 클릭합니다.
  2. PlayerHealth 스크립트를 선택하여 추가합니다.

이제 GameObject는 이동과 건강 관리 기능을 모두 갖추게 됩니다.

### 데이터 지향 프로그래밍 (Data-Oriented Programming, DOP)
최근 Unity는 데이터 지향 기술 스택(DOTS)을 도입하여, 데이터 지향 프로그래밍 패러다임을 지원합니다. 이는 성능을 극대화하기 위해 데이터를 캐시 친화적으로 구성하는 접근 방식입니다.

#### 장점
- **성능 향상**
  메모리 레이아웃을 최적화하여, 캐시 적중률을 높이고 성능을 극대화할 수 있습니다.
- **병렬 처리**
  멀티스레딩을 통해 여러 작업을 동시에 처리할 수 있습니다.
- **유지보수성**
  데이터와 로직을 분리하여, 코드의 유지보수성을 높일 수 있습니다.

#### 예시 코드 및 튜토리얼
1. 데이터 컴포넌트 정의
```cs
using Unity.Entities;

public struct Player : IComponentData
{
    public float speed;
    public int health;
}
```

2. 플레이어 시스템 정의
```cs
using Unity.Entities;
using Unity.Transforms;
using Unity.Mathematics;

public class PlayerSystem : SystemBase
{
    protected override void OnUpdate()
    {
        float deltaTime = Time.DeltaTime;

        Entities.ForEach((ref Translation translation, in Player player) =>
        {
            float move = Input.GetAxis("Horizontal") * player.speed * deltaTime;
            translation.Value.x += move;
        }).ScheduleParallel();
    }
}
```

3. Unity에서 ECS 설정하기
- Entity Manager 생성
  1. 새로운 빈 GameObject를 생성합니다.
  2. 빈 GameObject에 Convert To Entity 컴포넌트를 추가합니다.
- Player Entity 생성
  1. Player 데이터를 가진 프리팹을 생성합니다.
  2. 프리팹에 Convert To Entity 컴포넌트를 추가하여 Entity로 변환합니다.

이제 시스템은 프레임마다 플레이어 데이터를 업데이트하고, 이동 처리를 병렬로 수행하게 됩니다.

### 결론
각 패러다임은 고유의 장단점을 가지고 있으며, 프로젝트의 성격에 따라 적합한 패러다임을 선택하는 것이 중요합니다.

- **객체 지향 프로그래밍**은 소규모 프로젝트나 단순한 게임 로직에 적합합니다. 다만, 상속 계층이 깊어질 경우 코드 관리가 어려워질 수 있으므로, 이를 피하기 위해 적절한 디자인 패턴을 사용하는 것이 좋습니다.
- **컴포넌트 기반 프로그래밍**은 중대형 프로젝트에 유연성과 재사용성을 제공하여, 더 나은 유지보수성을 보장합니다. 여러 컴포넌트를 조합하여 기능을 구현하는 것이 핵심입니다.
- **데이터 지향 프로그래밍**은 성능이 중요한 대규모 프로젝트에 적합하며, 특히 멀티스레딩과 병렬 처리를 활용하는 게임에 유리합니다. ECS와 DOTS를 사용하여 성능을 극대화할 수 있습니다.

결론적으로, Unity에서 가장 적절한 패러다임은 프로젝트의 규모와 성격에 따라 다르며, 각 패러다임의 장점을 최대한 활용하는 것이 중요합니다.
