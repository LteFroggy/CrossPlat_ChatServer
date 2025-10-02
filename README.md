# CrossPlat_ChatServer
맥, Windows에서 모두 사용 가능한 채팅 서버를 만들기 위한 Repository

# 설치방법 
## vcpkg 설치하기
### 다운로드 및 설치
[vcpkg Github Link](https://github.com/microsoft/vcpkg)에 접속해서 zip으로 파일을 다운받는다.
압축을 풀고, **bootstrap-vcpkg.bat**을 실행한다.

### 환경 변수 설정
압축이 풀린 폴더를 원하는 위치로 이동시킨 후, **bootstrap-vcpkg.bat**이 존재하는 폴더를 시스템 환경변수 Path에 추가한다.

### 설치 확인 및 전역 처리
```vcpkg --version```을 사용해 설치가 잘 되었는지 확인한다.
잘 되었다면, ```vcpkg integrate install```을 활용해 vcpkg의 위치를 전역 경로로 등록해준다.
이를 수행하는 이유는, vcpkg에서 설치한 라이브러리를 Visual Studio 환경에서 사용 가능하도록 통합해주기 위함