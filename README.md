# Raytracer_in_c
## 개요

C 언어로 작성된 기본적인 그래픽 랜더링 프로그램입니다.
랜더링 모드는 두가지가 있습니다.
- Phong render (퐁 라이팅 모델 적용)
- Path Trace render (Path_tracing 알고리즘 적용)

### 주의
- C 언어 학습 목적으로 진행된 프로젝트이기 때문에, 코드 품질이 좋지 않을 수 있습니다.

## 설치
> 해당 프로젝트는 mac_os catalina 10.15 에서 제작되었고, 다른 환경에서 동작하지 않을 확률이 높습니다.

### 소스코드 다운로드

`git clone https://github.com/Likilee/raytracer_in_c.git`

### 실행파일 생성

`make all`

## 사용

첫 번째 인자로 `*.rt` 파일(**장면구성파일**) 을 넘겨주어 실행합니다.

ex) `./minirt ./rt/Fix/combination.rt`

프로그램을 실행하면 쉘에 아래와 같은 CLI 인터페이스와, 랜더링된 이미지가 그려지는 창이 나옵니다.

```
* = * = * = * = * = * = * = * = * = *
*                                   *
*            WELCOME TO             *
*             KILEE's               *
*            Raytracer              *
*                                   *
* = * = * LIGHT ON / OFF * = * = * =*
=          [ SPACE BAR ]            =
* = * = * FILTER CHANGE  * = * = * =*
=          [   F key   ]            =
* = * = * = * = * = * = * = * = * = *
***   MODE SWITCH by key press    ***
* = * = * = * = * = * = * = * = * = *
=     O key : object mode           =
*     L key : light mode            *
*     C key : camera mode           *
=     T key : trace(render) mode    =
* = * = * = * = * = * = * = * = * = *
```
이미지 윈도우를 활성 시킨 상태에서 단축키들을 통해 상호작용 가능합니다.

- `SPACE_BAR` : 조명을 On/Off 합니다. (랜더링 속도에 영향을 줍니다.)
- `F` : 이미지 필터를 변경합니다. (Default / Sepia / R / G / B 필터가 순회하며 적용됩니다.)
- `O` : 오브젝트 모드로 변경합니다. (오브젝트 모드에서는 장면에 있는 오브젝트를 선택하고 이동, 회전 시킬 수 있습니다.)
- `L` : 조명 모드로 변경합니다. (조명 모드에서는 조명을 선택하고 이동, 밝기를 조정할 수 있습니다.)
- `C` : 카메라 모드로 변경합니다. (카메라 모드에서는 카메라를 변경, 이동, 회전 할 수 있습니다.)
- `T` : 트레이스(랜더) 모드로 변경합니다. (트레이스 모드에서는 랜더링 알고리즘을 변경하고, 높은 품질의 랜더링 이미지를 얻을 수 있습니다.)

### 장면구성파일

- 장면구성파일 ( `*.rt` )은 `/rt` 에 위치합니다.
- 장면구성파일의 작성 규칙은 `/rt/rule.rt` 에 작성되어 있습니다.
- 규칙에 맞게 작성된 예제 장면구성파일들이 있습니다.
- 규칙에 맞게 장면구성파일

#### 장면구성파일 예제
- `/rt/scene.rt` : 빛과 몇몇 입체도형들의 상호작용을 위해 작성되었습니다. 해당 예제는 'Phong render' 모드만 지원합니다.
- `/rt/scene2.rt` : 고해상도에서 'Path Trace render' 모드의 결과를 확인하기 위해 작성되었습니다.
- `/rt/Fix/*` : 기타 코넬 박스 내에서의 오브젝트, skybox, combination 등의 예제가 들어 있습니다.

### Trace Mode

이미지 윈도우에서 `T` 키를 입력하면 아래와 같이 인터페이스가 변화하고 좀 더 높은 품질의 랜더링을 실행할 수 있습니다.
```
* = * = * = * MODE SWITCH = * = * = * = * = *
=  [ESC] [O]bject [L]ight [C]amera [T]race  =
* = * = * =  LIGHT ON / OFF * = * = * = * = *
=             [ SPACE BAR ]                 =
* = * = * = * FILTER CHANGE  * = * = * = * =*
=             [   F key   ]                 =
* = * = * = * = * = * = * = * = * = * = * = *
=              RENDER MODE                  =
* = * = * = * = * = * = * = * = * = * = * = *
=     --- --- ---            [ RENDER MODE ]=
*    | 1 | 2 |   |    1 : Phong render      *
=     --- --- ---     2 : Path_trace render =
* = * = * = * = * = * = * = * = * = * = * = *
= 1 : PHONG render                          =
=                                           =
* - Treat all object as phong diffuse model *
= - Only primary ray and Shadow ray         =
= - Sample per pixel(Antialiasing)          =
*                                           *
= 2 : PATH_TRACE render                     =
=                                           =
= - Treat material                          =
=   (Lambertain, Metal, Dielectric)         =
= - Sample per pixel(Antialiasing)          =
= - Scatter Depth                           =
* = * = * = * = * = * = * = * = * = * = * = *
```

#### Step1. `1` 도는 `2` 키를 입력하여 랜더링 모드를 선택합니다.

#### Step2. Sample per pixel 값 입력

랜더링 모드를 선택하면 CLI 인터페이스에서 아래와 같은 문구가 출력됩니다.
```
>> Ready for PHONG render
>> Type 'Sample per pixel' for Antialiasing
:
```

CLI 인터페이스에 한 픽셀당 Sampling 할 ray 수를 입력합니다. (입력한 숫자가 크면 오브젝트의 외곽선이 더욱 부드럽게 처리됩니다.)

#### Step3. 'Scatter depth' 설정 (Path Trace render 모드에서만 요구)

Path Trace render 모드에서는 아래와 같은 문구가 출력됩니다.
```
>> Type 'Scatter depth'
:
```

CLI 인터페이스에 Primary ray 가 최대한 몇번까지 산란(Scattering)할지를 결정합니다. (입력한 숫자가 크면 클 수록 더욱 사실적인 이미지가 그려집니다.)

#### Step4. Save rendered img
마지막으로 랜더링한 이미지를 저장할지 묻습니다.
```
>> Save RENDERED img?
>> : presss y/n)
```
이미지 윈도우에서 `Y` 키를 입력하면, 아래와 같이 파일명 입력을 요구합니다.

```
>> Type save file name (MUST end with '.bmp'
:
```
파일명은 `*.bmp` 형식이어야합니다. 생성된 이미지는 `/bmp` 에 저장됩니다.