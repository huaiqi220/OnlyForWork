## 如何实现敌人高亮

Controller中查询指针下面Actor是不是继承Aura_Enemy?
- 这方法不行，会导致Controller依赖于Aura_Enemy，不够通用

**如何使代码更通用？**

使用接口

项目设置中打开：自定义深度 使用模板

放置后处理体积，设置无限大

对Mesh启动渲染自定义深度pass，设置深度值为材质中的规定值