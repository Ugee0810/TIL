# 2024-07-06
**Tags**: `unity`, `ar`

## What I Learned
오늘은 Unity 6에서 AR Foundation을 탐구했습니다.
AR Foundation은 Android와 iOS 모두에서 AR 애플리케이션을 구축하기 위한 크로스 플랫폼 프레임워크입니다. ARKit(IOS) 및 ARCore(Android)를 활용하여 AR 기능을 위한 통합 API를 제공합니다. 이 프레임워크는 기본 AR 플랫폼 간의 차이점을 추상화하여 AR 경험을 만드는 과정을 간소화하도록 설계되었습니다.

### Additional Books, Documents, Articles Read
- **Unity Documentation on AR Foundation** : 이 문서는 Unity에서 AR Foundation을 설정하고 사용하는 방법에 대한 종합적인 가이드를 제공합니다. 설치, 구성 및 일반적인 사용 사례를 다룹니다.
- **AR Foundation Samples** : 이 GitHub 리포지토리에는 평면 탐지, 이미지 추적 및 얼굴 추적 등 AR Foundation의 다양한 기능을 시연하는 예제 프로젝트가 포함되어 있습니다.
- **ARCore Developer Guide** : Android 측에서 사용 가능한 기능에 대한 자세한 내용을 제공하는 Google의 공식 가이드입니다.
- **ARKit Developer Guide** : iOS 개발을 위한 기능을 설명하는 Apple의 공식 문서입니다.

## Example
```cs
using UnityEngine;
using UnityEngine.XR.ARFoundation;
using UnityEngine.XR.ARSubsystems;

public class SimpleAR : MonoBehaviour
{
    [SerializeField]
    private ARSessionOrigin arSessionOrigin;
    [SerializeField]
    private ARPlaneManager arPlaneManager;

    void Start()
    {
        // 장치에서 AR이 지원되는지 확인합니다.
        if (ARSession.state == ARSessionState.Unsupported)
        {
            Debug.Log("이 장치에서는 AR이 지원되지 않습니다.");
            return;
        }

        // AR 세션 활성화
        arSessionOrigin.MakeContentAppearAt(transform, Vector3.zero);
        arPlaneManager.enabled = true;
    }

    void Update()
    {
        // AR 업데이트 처리
        if (ARSession.state == ARSessionState.SessionTracking)
        {
            // AR 관련 작업 수행
        }
    }
}
```
AR 세션을 초기화하고 장치가 AR을 지원하는지 확인합니다. 또한 ARPlaneManager를 활성화하여 환경에서 평면을 감지하기 시작합니다.

## Resources
- [Unity AR Foundation Documentation](https://docs.unity3d.com/Packages/com.unity.xr.arfoundation@6.0/manual/index.html)
- [AR Foundation Samples on GitHub](https://github.com/Unity-Technologies/arfoundation-samples)
- [Google ARCore Developer Guide](https://developers.google.com/ar/develop/java/quickstart?hl=ko)
- [Apple ARKit Developer Guide](https://developer.apple.com/documentation/arkit)
