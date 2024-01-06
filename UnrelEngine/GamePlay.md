

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
- UI写在哪，UI因为与玩家有关，最好写在PlayerController里面,而不要写到GameMode里面，也不要写到关卡蓝图里面。

- AI的灵魂
  - 什么东西适合写进AIController？
  - 什么层级写什么层级的东西
  - HP是关系游戏逻辑的属性，所以应该写到State里面，而不是写到AIController里面。客户端是无法信任的
- 行为树功能强大
- 黑板共享数据
- AI感知
- EQS环境查询


### ULevel 关卡

- Actor的集合
- World里的一个板块
- 对应umap

### UWorld 世界
- Level的集合
- 运行时真正的Actor集合
- World可同时存在多个，好比如客户端World和服务端World

### AGameMode && AGameState

- GameMode是关卡的逻辑,是世界的规则
- 最权威

- GameState是世界状态
- 通知到各端

### UGameInstance 游戏实例 USaveGame 存档

- 整场游戏的全局实例
- World的外围管理对象，管理多个世界
- 跨关卡的逻辑

- 游戏存档
  - 背包数据写到哪？背包可能会写到PlayerState里面,等保存时再同步存到USaveGame里面。
- 如何保存游戏过程中动态生成的Actor
  - Actor本身不会被保存，能保存的是数据，在重新加载场景的时候进行恢复

### USubsystem 子系统
- 业务逻辑的组件
- 5个生命周期粒度控制
- 自动生成对象
- 托管生命周期
- 替代Manager类

### 什么逻辑在哪里

- Component： 功能，能力
- Actor: 个体本身的逻辑
- APawn -- APlayerController -- APlayerState 主角肉体-灵魂-状态
- APawn -- AAIController -- AAIState AI肉体-灵魂-状态
- AAIController -- BehaviorTree -- BlackBoard AI灵魂-行为树-数据
- AGameMode -- AGameState 游戏规则-游戏状态
- UGameInstance -- USaveGame 全局游戏实例-游戏存档
- USubsystem 游戏逻辑组件

### 输入事件在哪里处理？

- 考虑联机扩展
- APlayerController最优先
- APawn其次
- AActorEnableInput
- 关卡蓝图随便测测

### 联机的角色职责

- 谁在那里
- 谁复制了

### GamePlay里带Damage好不好
**不纯粹？**
- 统一的伤害接口
- 破碎，游戏逻辑，GAS

### 如何创建类似元神第三人称视角游戏

设置弹簧臂不继承Pawn旋转
```cpp
AAuraCharacter::AAuraCharacter()
{
	// 这行代码设置角色的旋转方向以匹配其移动方向。当这个属性被设置为 true 时，角色会自动朝向它正在移动的方向。 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//  这行代码设置了角色旋转的速率。这里的 FRotator 是一个旋转值，分别代表绕着X轴、Y轴和Z轴的旋转速度。
	//  在这个例子中，设置的是绕Y轴（通常是上下旋转）旋转400度每秒，而绕X轴和Z轴的旋转速度则是0。
	GetCharacterMovement()->RotationRate = FRotator(0.f,400.f,0.f);
	// 这行代码确保角色的移动被限制在一个平面内。这通常用于2D游戏或需要限制角色不在三维空间中上下移动的场景。
	GetCharacterMovement()->bConstrainToPlane = true;
	// 当这个属性设置为 true 时，角色将在游戏开始时自动对齐到约束平面上。这对于确保角色始终保持在特定的游戏平面上很有帮助。
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	// 这行代码设置角色不使用控制器（如游戏手柄或键盘）的俯仰（pitch，即上下）旋转。这意味着角色的上下朝向不会根据控制器的俯仰输入改变。
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	/*
	*是的，控制器的旋转通常指的是输入设备（如游戏手柄或鼠标）提供的旋转输入。在虚幻引擎（Unreal Engine）的上下文中，这涉及到几个方面：
	1. **俯仰（Pitch）**: 控制器俯仰通常指的是视角或角色的上下移动。在游戏手柄上，这可能由摇杆的上下移动控制；在使用鼠标的情况下，通常是鼠标的前后移动。
	2. **偏航（Yaw）**: 控制器偏航指的是左右转向。在游戏手柄上，这通常是通过摇杆的左右移动来控制的；在鼠标控制的情况下，通常是鼠标的左右移动。
	3. **翻滚（Roll）**: 控制器翻滚较少用于标准游戏控制，通常指的是围绕前进方向的旋转。在某些飞行模拟游戏中可能会用到。
	在您的代码段中，将 `bUseControllerRotationPitch`、`bUseControllerRotationYaw` 和 `bUseControllerRotationRoll` 都设置为 `false`
	意味着角色的这些方向的旋转不会根据控制器的输入来改变。
	这通常用于创建角色自动朝向其移动方向的效果，而不是由玩家直接控制其朝向。
	这种设置在第三人称游戏中非常常见，其中角色的移动和方向更多地由游戏逻辑控制，而不是直接通过玩家的输入。
	 */
}
```