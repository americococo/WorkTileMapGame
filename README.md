# WorkTileMapGame
나는아무생각이없다.(타일맵)

- 턴제 RPG TileGame
 -Map 게임맵 클래스 맵상의 존재하는 모든 객체들은 map객체내에 존재
  -TileCell 맵객체를 이루고있는 작은 요소
   - TileObject하나의 셀에 들어가는 오브젝트들

 - SelfMoveOjbect 스스로 움직이는 오브젝트들
  - Playable 캐릭터
  - Monster


### 오브젝트 정보
| 분류 | SelfMoveOjbect | Monster | Item|
| :--------: | :--------: | :--------: | :--------: |
| 이 동 | 키보드 입력 | Ai        | 이동하지않음|
|  생성 레이어 | 지상(스킬사용시 공중)    | 지상,공중 | 지상,공중|
| 타입 |   육성형  |   공격특화형,방어특화형,밸런스형,도주형     |버프,순간적용력| 

###### ※(현)타입  미구현
###### ※(현)레벨  미구현

### 오브젝트별 타입 상세정보
1. SelfMoveOjbect
    ===
  - 육성형
   - ※육성형외 특징을 가진 오브젝트들은 레벨이 존재하지 않는다.
   - 플레이어만이 가지고있는 타입으로 경험치를 얻으며 레벨업을 하며 점점 강해짐


2. Monster
    ===
 - 공격특화형
  - 공격력이 매우높은 개체
  - 일정거리안에 적이 존재할시 추적(추적 방법  ↓아래↓)
  
 - 방어특화형
  -생존력이 높은 개체
   -방어특화형은 두가지로 분류되며 한 분류는 체력이 매우 높고 또 한 개체는 방어력이 매우 낮다.
   - 공격이 매우 낫게 설정되있다.
   

  [구현방식 과거 22DTileMap게임제작시 사용한 기법중 일부](https://github.com/americococo/2DTileMap/blob/master/titleM/Monster.cpp)
  ~~~
  std::vector<eComponentType> compareTpyeList;
  		compareTpyeList.push_back(eComponentType::CT_NPC);
  		compareTpyeList.push_back(eComponentType::CT_PLAYER);
      FindComponentInRange(map, this, 5, compareTpyeList);
  ~~~
