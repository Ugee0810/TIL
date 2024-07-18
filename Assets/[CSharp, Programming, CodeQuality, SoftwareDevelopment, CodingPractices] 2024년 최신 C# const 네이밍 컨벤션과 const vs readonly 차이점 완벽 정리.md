# 2024-07-18
**Tags**: `CSharp`, `Programming`, `CodeQuality`, `SoftwareDevelopment`, `CodingPractices`

## 2024년 최신 C# const 네이밍 컨벤션과 const vs readonly 차이점 완벽 정리
### 2024년 최신 C# const 네이밍 컨벤션
C#에서 상수를 정의할 때 사용하는 const 키워드는 코드의 가독성과 유지보수성을 높이는 데 중요한 역할을 합니다. 2024년 현재, 최신의 C# const 네이밍 컨벤션은 다음과 같습니다.

#### 1. PascalCase 사용
상수의 이름은 PascalCase로 작성합니다. 예를 들어, `MaxCount`, `DefaultTimeout` 등이 있습니다.

```cs
public const int MaxCount = 100;
public const string DefaultMessage = "Hello, World!";
```

#### 2. 명확하고 설명적인 이름 사용
상수의 이름은 해당 값의 목적을 명확히 나타내야 합니다.

```cs
public const int DefaultTimeoutInSeconds = 30;
```

### readonly와 const의 특징과 차이점
C#에서 `const`와 `readonly` 키워드는 상수 값을 정의하는 데 사용되지만, 각각의 특징과 용도가 다릅니다.

#### const
- **컴파일 시간 상수**: 값이 컴파일 시간에 결정됩니다.
- **암시적 정적**: 클래스 수준에서 접근됩니다.
- **변경 불가**: 선언 시 값이 고정됩니다.
- **리터럴 값만 가능**: 기본 형식 또는 문자열이어야 합니다.

```cs
public const int MaxValue = 100;
```

#### readonly
- **런타임 상수**: 값이 런타임에 한 번만 설정됩니다.
- **인스턴스 또는 정적**: 인스턴스 또는 정적으로 정의할 수 있습니다.
- **복잡한 값 가능**: 객체 참조, 구조체 등 다양한 값이 가능합니다.
- **생성자에서 설정 가능**: 생성자에서 초기화할 수 있습니다.

```cs
public readonly int maxValue;

public MyClass()
{
    maxValue = GetMaxValueFromConfig();
}

private int GetMaxValueFromConfig()
{
    return 100;
}
```

### 메서드 안과 밖에서 선언할 때 각각의 특징과 사례
#### 메서드 내부에 `const` 또는 `readonly` 선언
메서드 내부에서 `const` 또는 `readonly`를 선언할 때의 예시입니다.

```cs
public void ProcessData()
{
    const int bufferSize = 1024;
    readonly int maxAttempts = GetMaxAttempts();

    for (int i = 0; i < bufferSize; i++)
    {
        // 데이터 처리 로직
    }
}
```

- **가독성**: 메서드 내부에서 사용되는 상수를 명확히 할 수 있습니다.
- **유지보수성**: 해당 상수가 메서드 내부에서만 사용됨을 보장합니다.

#### 메서드 외부에 const 또는 readonly 선언
메서드 외부, 클래스 수준에서 const 또는 readonly를 선언할 때의 예시입니다.

```cs
private const int BufferSize = 1024;
private readonly int MaxAttempts;

public MyClass()
{
    MaxAttempts = GetMaxAttempts();
}

public void ProcessData()
{
    for (int i = 0; i < BufferSize; i++)
    {
        // 데이터 처리 로직
    }
}
```

- **가독성**: 클래스 전반에 걸쳐 상수의 사용을 일관되게 유지할 수 있습니다.
- **유지보수성**: 여러 메서드에서 동일한 상수를 사용할 수 있습니다.

### 컴파일 시간과 런타임 시간이란?
#### 컴파일 시간 (Compile Time)
- **정의**: 소스 코드가 기계어로 번역되는 시간입니다. 이 과정은 컴파일러가 소스 코드를 분석하고, 오류를 확인하고, 실행 파일(예: .exe, .dll)을 생성하는 동안 발생합니다.
- **속도**: 컴파일 시간은 개발 프로세스 중 발생하며, 프로그램 실행 전의 단계입니다. 컴파일 시간에 결정되는 값들은 이미 컴파일된 결과물에 포함되어 있어 실행 시 추가적인 초기화나 연산이 필요하지 않습니다.
- **예시**: `const` 키워드를 사용하여 선언된 상수는 컴파일 시간에 결정됩니다. 예를 들어, 다음 코드는 컴파일 시에 `MaxValue`를 100으로 설정합니다.

```cs
public const int MaxValue = 100;
```

#### 런타임 시간 (Run Time)
- **정의**: 컴파일된 프로그램이 실행되는 시간입니다. 이 과정은 실제 프로그램이 사용자의 요청에 따라 동작하는 동안 발생합니다.
- **속도**: 런타임 시간은 프로그램이 실제로 실행되고 있는 동안 발생하는 시간입니다. 런타임에 값을 결정하는 작업은 실행 시마다 반복되므로 컴파일 시간에 비해 상대적으로 느릴 수 있습니다.
- **예시**: `readonly` 키워드를 사용하여 선언된 상수는 프로그램이 실행되는 동안, 주로 생성자에서 초기화됩니다. 예를 들어, 다음 코드는 런타임에 `maxValue`를 설정합니다.

```cs
public class MyClass
{
    public readonly int maxValue;

    public MyClass()
    {
        maxValue = GetMaxValueFromConfig();
    }

    private int GetMaxValueFromConfig()
    {
        // 런타임에 결정되는 값을 반환
        return 100;
    }
}
```

### 결론
C#에서 상수를 정의할 때, 상황에 따라 `const`와 `readonly`를 적절히 사용하는 것이 중요합니다. 컴파일 시간에 결정되는 값은 `const`를 사용하고, 런타임에 한 번 설정되는 값은 `readonly`를 사용하는 것이 바람직합니다. 또한, 상수의 범위와 사용 목적에 따라 메서드 내부 또는 외부에 선언하여 코드의 가독성과 유지보수성을 높일 수 있습니다.
