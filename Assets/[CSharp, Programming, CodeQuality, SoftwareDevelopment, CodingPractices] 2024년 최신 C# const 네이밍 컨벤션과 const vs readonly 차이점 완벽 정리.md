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
C#에서 `const`와 `readonly` 키워드는 상수 값을 정의하는 데 사용되지만, 각각의 특징과 용도가 다릅니다. 현업에서 전문적인 지식을 도움받을 수 있는 수준으로 자세히 설명하겠습니다.

#### const
**컴파일 시간 상수**
- **정의**: `const`로 선언된 상수는 컴파일 시간에 값이 결정되며, 프로그램이 컴파일될 때 코드에서 상수 값이 직접적으로 대체됩니다.
- **사용 예시**: 주로 변경되지 않는 리터럴 값에 사용됩니다.

```cs
public const int MaxValue = 100;
```

**암시적 정적**
- **정의**: const로 선언된 상수는 암시적으로 static이며, 인스턴스가 아닌 클래스 수준에서 접근할 수 있습니다. 따라서 클래스의 모든 인스턴스가 동일한 값을 공유합니다.
- **사용 예시**: 클래스 내에서 공통적으로 사용되는 값에 적합합니다.

```cs
public class MyClass
{
    public const string Greeting = "Hello";
}

MyClass.Greeting;  // "Hello"
```

**리터럴 값만 가능**
- **정의**: const 상수는 리터럴 값만 가능합니다. 즉, 기본형(정수형, 실수형, 문자형, 문자열 등)이나 열거형 값이어야 합니다.
- **사용 예시**: 객체 참조나 복잡한 계산 결과는 사용할 수 없습니다.

```cs
public const double Pi = 3.14159;
```

#### readonly
**런타임 상수**
- **정의**: readonly로 선언된 상수는 프로그램 실행 시, 즉 런타임에 값이 설정됩니다. 이 값은 생성자에서 설정할 수 있으며, 초기화된 이후에는 변경할 수 없습니다.
- **사용 예시**: 생성자에서 초기화해야 하는 값에 적합합니다.

```cs
public readonly int MaxValue;

public MyClass()
{
    MaxValue = GetMaxValueFromConfig();
}
```

**인스턴스 또는 정적**
- **정의**: readonly 필드는 인스턴스 필드로 선언될 수 있으며, 각 인스턴스마다 고유한 값을 가질 수 있습니다. 또한 static readonly로 선언하면 클래스 수준에서 단 하나의 값을 공유합니다.
- **사용 예시**: 특정 인스턴스마다 다른 값을 가져야 하는 경우나 클래스 수준에서 한 번 설정되어야 하는 경우에 유용합니다.

```cs
public class MyClass
{
    public static readonly int MaxItems = 100;

    public MyClass()
    {
        MaxItems = 200; // 컴파일 오류 발생
    }
}
```

**복잡한 값 가능**
- **정의**: readonly 필드는 객체 참조나 구조체, 배열 등 복잡한 타입의 값을 가질 수 있습니다. 생성자에서 복잡한 초기화 로직을 통해 설정할 수 있습니다.
- **사용 예시**: 클래스나 구조체 인스턴스, 컬렉션 등의 초기화가 필요한 경우에 적합합니다.

```cs
public readonly List<string> Names;

public MyClass()
{
    Names = new List<string> { "Alice", "Bob" };
}
```

### 메서드 안과 밖에서 선언할 때 각각의 특징과 장점
#### 메서드 내부에 `const` 또는 `readonly` 선언
메서드 내부에서 `const` 또는 `readonly`를 선언하는 경우, 다음과 같은 특징이 있습니다.

**1. 명확한 범위**
상수나 읽기 전용 변수가 메서드 내에서만 사용될 때, 해당 메서드 내부에 선언하면 그 범위가 명확해집니다. 이는 코드의 가독성을 높이고 유지보수를 용이하게 합니다.

```cs
public void ProcessData()
{
    const int BufferSize = 1024;
    readonly int maxAttempts = GetMaxAttempts();

    for (int i = 0; i < BufferSize; i++)
    {
        // 데이터 처리 로직
    }
}
```

**2. 메모리 관리**
메서드 내부에 선언된 변수는 메서드가 실행될 때만 메모리에 존재합니다. 이는 메모리 사용량을 줄이는 데 도움이 될 수 있습니다. 주로 짧은 생명 주기를 가지는 상수 값에 적합합니다.

#### 메서드 외부에 const 또는 readonly 선언
메서드 외부, 즉 클래스 수준에서 const 또는 readonly를 선언하는 경우, 다음과 같은 특징이 있습니다.

**1. 재사용성**
클래스 내 여러 메서드에서 동일한 값을 사용할 수 있습니다. 이는 코드의 일관성을 유지하고 중복을 줄이는 데 도움이 됩니다.

```cs
private const int BufferSize = 1024;
private readonly int maxAttempts;

public MyClass()
{
    maxAttempts = GetMaxAttempts();
}

public void ProcessData()
{
    for (int i = 0; i < BufferSize; i++)
    {
        // 데이터 처리 로직
    }
}

public void AnotherMethod()
{
    Console.WriteLine($"Max Attempts: {maxAttempts}");
}
```

**2. 초기화 논리 분리**
복잡한 초기화 논리를 생성자나 초기화 블록에서 분리하여 작성할 수 있습니다. 이는 코드의 가독성을 높이고 초기화 로직을 보다 명확하게 분리하는 데 도움이 됩니다.

```cs
public class MyClass
{
    public readonly List<string> Names;

    public MyClass()
    {
        Names = InitializeNames();
    }

    private List<string> InitializeNames()
    {
        // 복잡한 초기화 로직
        return new List<string> { "Alice", "Bob" };
    }
}
```

**3. 상태 공유**
클래스 수준의 상수나 읽기 전용 변수를 통해 클래스의 모든 인스턴스 간에 상태를 공유할 수 있습니다. 이는 특정 값이 클래스의 모든 인스턴스에서 동일하게 유지되어야 하는 경우에 유용합니다.

```cs
public class MyClass
{
    public static readonly int MaxItems = 100;

    public void DisplayMaxItems()
    {
        Console.WriteLine($"Max Items: {MaxItems}");
    }
}
```

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
