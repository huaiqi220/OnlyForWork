

## GamePlay

- 什么逻辑写在哪里

- 各个类的职责是什么

- 从属交互关系

- 如何表现一个系统的多方面

- 哪些写法是不太好的

- 常见的一些问题和误区

### Actor 演员、个体

- **组成世界的单位个体**
  场景中的所有单位都是Actor,包括World Settings也是一个Actor,关卡蓝图也是一个Actor，相当于搭建环境的最小积木
- **可相互嵌套**
  不同Actor之间可以有关系，如父子关系等。
- **组件的容器**
  - 如果Actor是空的，他就无法实现很多的功能，Actor通过-组件来实现各种功能。本身，是一个比较空的东西。
  - 好比如说这里有个方块，他为什么是个方块，是因为他有一个配置为立方体的静态网格组件。
  - 如果在此处添加物理组件，这个Actor就会附加物理属性。
  - 如果带一个碰撞组件，就会有碰撞的效果。
  - 可以自己写一个比较通用的Component，然后可以在不同的Actor上复用
- **Spawn & Tick**
- **网络通信的通道**
- **派生出各种不同职责的Actor**
  - Actor本身可以派生出许多不同的类，类具有许多的不同的功能。APawn、AController、AInfo、AHUD、APlayerCameraManager、Others。**不是所有的Actor都看得见。**

### Component 组件
- 组件是种能力，为Actor提供能力
  - 游戏中可以抽象出来的，可以复用的一些功能
- 能力一般跟业务逻辑无关
  - 不太建议把爆率、掉落等游戏逻辑写到组件里面
  - 抛射组件、按格子走路的能力，可以写到组件里
  - 有个标准，当我做另外一款游戏的时候，这个能力可以拿到另外一个游戏里复用。
- 能力是跨游戏的，可以复用
- Actor是互动单位，Component是能力单位

#### SceneComponent 场景组件 和 ActorComponent 演员组件

ActorComponent不带有空间上的关系，所以不具有世界坐标。如移动。如果具有空间关系，就需要定义一个SceneComponent。

### ALevelScriptActor 关卡蓝图

- 一个特殊的默认脚本Actor:ALevelScriptActor

- 正经项目-大部分情况下都不适合
    - 大部分情况下都不用在里面写东西。除非做一些小demo，快速功能验证。
    - 关卡蓝图只有一个，逻辑多了会越来越复杂。
- 适合demo，新手村
- 适合一些关卡本身的触发机械互动

### APawn 演员
- 一个可以被控制的Actor
- 逻辑足够复杂就要MVC设计
  - APawn相比Actor足够复杂，比较关键的就是有控制器的APawn
  
- 肉体
  - Pawn Controller state三者关系，Pawn像是肉体、机甲，而应该把hp、mp、攻击力、防御力等属性放到State里面，这样Controller控制另外一个Pawn，好比如从Character切换到另外固定机枪等等，同样可以获取到状态。
- 人形角色

### AController && APlayerState
- Controller是控制别的Actor的Actor，本身不带位置，类似于“灵魂”，重点在于逻辑
- 灵魂
- 肉体状态
- 抽离开是为了联机复制
  - 在联机的时候，单独的把state复制到客户端上去。

### APlayerController && AAIController
- 主角的灵魂
- 和玩家沟通的渠道
  - 玩家和游戏联系的通道，就是通过PlayerController扩散到别的Actor上去。
- 写最多的是输入内容，或者一些Camera，跟玩家直接交互的内容

- AI的灵魂
- 行为树功能强大
- 黑板共享数据
- AI感知
- EQS环境查询