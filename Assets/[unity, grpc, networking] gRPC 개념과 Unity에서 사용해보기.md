
# 2024-07-08
**Tags**: `unity`, `grpc`, `networking`

## What I Learned
### REST와 gRPC 간단한 설명
Unity에서는 HTTP 요청을 간단히 처리할 수 있는 RESTful API를 사용하는 것이 일반적입니다. 하지만 REST보다 속도와 효율성이 중요할 때는 gRPC가 유리합니다. gRPC는 Protocol Buffers를 사용하여 직렬화하고, HTTP/2를 통해 효율적으로 통신할 수 있어 REST보다 빠르고 성능이 우수합니다. 특히 대규모 데이터 처리나 실시간 서비스에 적합합니다. 보다 깊은 근거는 다음의 [테스트 레퍼런스](https://cla9.tistory.com/177)를 참고해주세요.

### gRPC 개요
gRPC는 구글에서 개발한 고성능의 RPC(원격 프로시저 호출) 프레임워크입니다. 주로 분산 시스템 간 통신을 위해 사용되며, Protocol Buffers(ProtoBuf)를 기반으로 데이터 직렬화를 지원합니다. gRPC는 HTTP/2 기반의 양방향 스트리밍을 지원하여 더욱 효율적인 네트워크 통신을 가능하게 합니다.

### gRPC 사용하기
- [초기 세팅 참조 문서](https://unity3d.tistory.com/2)

1. Grpc.Core 라이브러리 사용
gRPC를 사용하기 위해서는 먼저 Grpc.Core 네임스페이스를 사용할 수 있도록 using 문을 추가해야 합니다.

```cs
using Grpc.Core;
```

2. 서비스 정의와 구현
gRPC 서비스는 Protocol Buffers를 사용하여 서비스와 메시지를 정의합니다. 예를 들어, ImageService 클래스는 ImageService.ImageServiceBase 클래스를 상속받아 서버 측 gRPC 서비스를 구현합니다.

## Example
### 📜 Unity에서 gRPC를 이용한 10MB 이하 이미지 파일 전송
#### ProtoBuf 정의하기
먼저, 이미지 파일 전송을 위한 .proto 파일을 정의합니다.

```protobuf
syntax = "proto3";

message ImageData {
    bytes data = 1;
}

service ImageService {
    rpc UploadImage(ImageData) returns (google.protobuf.Empty);
}
```

#### 서버 구현하기
서버 측에서는 위에서 정의한 RPC를 구현합니다.

```cs
using Grpc.Core;
using System.Threading.Tasks;
using System.IO;

public class ImageService : ImageService.ImageServiceBase
{
    public override Task<Google.Protobuf.WellKnownTypes.Empty> UploadImage(ImageData request, ServerCallContext context)
    {
        // 이미지 데이터 처리 로직 예시: 이미지 저장
        string imagePath = $"path_to_save_image_directory/{context.Peer}_{DateTime.UtcNow.Ticks}.jpg"; // 파일 경로 설정
        try
        {
            // 이미지 데이터를 파일로 저장
            File.WriteAllBytes(imagePath, request.Data.ToByteArray());
            Console.WriteLine($"Image saved: {imagePath}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Failed to save image: {ex.Message}");
            throw; // 예외 처리
        }

        return Task.FromResult(new Google.Protobuf.WellKnownTypes.Empty());
    }
}
```

#### 클라이언트 구현하기
클라이언트 측에서 gRPC를 통해 이미지를 서버에 전송합니다.

```cs
using Grpc.Core;
using System;
using UnityEngine;

public class ImageUploader : MonoBehaviour
{
    private Channel channel;
    private ImageService.ImageServiceClient client;

    private async void Start()
    {
        channel = new Channel("localhost:50051", ChannelCredentials.Insecure);
        client = new ImageService.ImageServiceClient(channel);

        // 이미지 데이터 읽기
        byte[] imageData = ReadImageFile();

        // gRPC 요청 보내기
        await client.UploadImageAsync(new ImageData { Data = Google.Protobuf.ByteString.CopyFrom(imageData) });

        Debug.Log("Image uploaded successfully.");

        // 채널 종료
        await channel.ShutdownAsync();
    }

    private byte[] ReadImageFile()
    {
        string imagePath = "path_to_your_image.jpg"; // 이미지 파일 경로
        return System.IO.File.ReadAllBytes(imagePath);
    }

    private void OnDestroy()
    {
        if (channel != null)
        {
            channel.ShutdownAsync().Wait();
        }
    }
}
```

### 📜 Unity에서 gRPC를 이용한 멀티플레이어 게임 세션 및 플레이어 이동 동기화
#### ProtoBuf 정의하기
게임 세션 및 플레이어 이동 동기화를 위한 .proto 파일을 정의합니다.

```protobuf
syntax = "proto3";

message PlayerPosition {
    float x = 1;
    float y = 2;
    float z = 3;
}

message PlayerMoveRequest {
    PlayerPosition position = 1;
}

message PlayerMoveResponse {
    string message = 1;
}

service GameService {
    rpc SendPlayerMove(PlayerMoveRequest) returns (PlayerMoveResponse);
    // 필요에 따라 추가 RPC 정의 가능
}
```

#### 서버 구현하기
서버 측에서는 게임 세션을 관리하고 플레이어의 이동을 동기화하는 로직을 구현합니다.
```cs
using Grpc.Core;
using System.Collections.Generic;
using UnityEngine;

public class GameService : GameService.GameServiceBase
{
    private static Dictionary<string, PlayerPosition> playerPositions = new Dictionary<string, PlayerPosition>();

    public override Task<PlayerMoveResponse> SendPlayerMove(PlayerMoveRequest request, ServerCallContext context)
    {
        // 클라이언트에서 받은 플레이어 위치 정보를 업데이트
        playerPositions[context.Peer] = request.Position;

        // 동기화할 메시지 생성
        string syncMessage = $"Player moved to ({request.Position.X}, {request.Position.Y}, {request.Position.Z})";

        // 다른 플레이어들에게 플레이어 이동 정보 전송 (예: 다른 클라이언트로 메시지 보내기)

        return Task.FromResult(new PlayerMoveResponse { Message = syncMessage });
    }
}
```

#### 클라이언트 구현하기
```cs
클라이언트 측에서 gRPC를 통해 게임 서버와 통신하고 플레이어 이동을 동기화합니다.
using Grpc.Core;
using System.Threading.Tasks;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    private Channel channel;
    private GameService.GameServiceClient client;

    private async void Start()
    {
        channel = new Channel("localhost:50051", ChannelCredentials.Insecure);
        client = new GameService.GameServiceClient(channel);

        // 게임 시작 시 초기 위치 전송
        await SendPlayerMoveAsync(new PlayerPosition { X = transform.position.x, Y = transform.position.y, Z = transform.position.z });
    }

    private async Task SendPlayerMoveAsync(PlayerPosition position)
    {
        // 플레이어 이동 정보를 서버에 전송
        var response = await client.SendPlayerMoveAsync(new PlayerMoveRequest { Position = position });
        Debug.Log($"Server responded: {response.Message}");
    }

    private void Update()
    {
        // 플레이어의 위치 업데이트 로직
        // 예: 키보드 입력에 따라 플레이어 이동
        if (Input.GetKey(KeyCode.W))
        {
            transform.Translate(Vector3.forward * Time.deltaTime);
            SendPlayerMoveAsync(new PlayerPosition { X = transform.position.x, Y = transform.position.y, Z = transform.position.z });
        }
        // 추가 이동 로직 구현 가능
    }

    private void OnDestroy()
    {
        if (channel != null)
        {
            channel.ShutdownAsync().Wait();
        }
    }
}
```

## Resources
- Tistory@cla9 - [테스트 레퍼런스](https://cla9.tistory.com/177)
- Tistory@GiantKing - [초기 세팅 참조 문서](https://unity3d.tistory.com/2)
