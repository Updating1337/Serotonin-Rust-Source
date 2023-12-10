#pragma once

#include <string>
#include <vector>

#define SUPPORTED_LANGUAGES 2
#define ENGLISH 0
#define CHINESE 1
#define RUSSIAN 2

#define TXTRust
inline const int LANG = ENGLISH;

#define LOCALIZATION(name, english, chinese, russian) inline LocalizedName name(english, chinese, russian)

//#ifndef TXTRust
//#define LOCALIZATION(name, english, chinese, russian) inline LocalizedName name(english)
//#else
//#define LOCALIZATION(name, english, chinese, russian) inline LocalizedName name(chinese)
//#endif

struct LocalizedName {
	std::vector<std::string> names;
	//std::string name;
	LocalizedName(const char* english, const char* chinese, const char* russian)
	{
		names.reserve(SUPPORTED_LANGUAGES + 1);
		//name = english;
		names.emplace_back(english);
		names.emplace_back(chinese);
		names.emplace_back(russian);
	}

	__declspec(noinline) const char* operator()() const noexcept
	{
		if (LANG > SUPPORTED_LANGUAGES)
			return names[ENGLISH].c_str();

		return names[LANG].c_str();
	}

	__declspec(noinline) const std::string& str() const noexcept
	{
		if (LANG > SUPPORTED_LANGUAGES)
			return names[ENGLISH];

		return names[LANG];
	};
};

namespace Translator {
	inline std::string english = XS("English");
	//inline std::string chinese = XS("中文");
	//inline std::string russian = XS("Русский");

	LOCALIZATION(AimbotTab, XS("Aimbot"), XS("自动瞄准"), XS("АИМБОТ"));
	LOCALIZATION(RageTab, XS("Rage"), XS("愤怒"), XS("Ярость"));
	LOCALIZATION(VisualsTab, XS("Visuals"), XS("视觉"), XS("Визуальный"));
	LOCALIZATION(ChamsTab, XS("Chams"), XS("查姆斯"), XS("Luminescence"));
	LOCALIZATION(World1Tab, XS("World-1"), XS("世界-1"), XS("Мир-1"));
	LOCALIZATION(World2Tab, XS("World-2"), XS("世界-2"), XS("Мир-2"));
	LOCALIZATION(World3Tab, XS("World-3"), XS("世界-3"), XS("Мир-3"));
	LOCALIZATION(PlayerTab, XS("Player"), XS("球员"), XS("Игрок"));
	LOCALIZATION(MiscTab, XS("Misc"), XS("杂项"), XS("разное"));
	LOCALIZATION(WeatherTab, XS("Weather"), XS("天气"), XS("Погода"));
	LOCALIZATION(WeaponTab, XS("Weapon"), XS("武器"), XS("Оружие"));
	LOCALIZATION(SettingsTab, XS("Settings"), XS("设置"), XS("Настройки"));

	LOCALIZATION(Language, XS("English"), XS("中文"), XS("Русский"));


	namespace Aimbot {

		LOCALIZATION(generaltab, XS("General"), XS("般的"), XS("Общий"));
		LOCALIZATION(magictab, XS("Magic"), XS("魔法"), XS("Магия"));
		LOCALIZATION(bullettab, XS("Bullet"), XS("子弹"), XS("пуля"));
		LOCALIZATION(exploittab, XS("Exploits"), XS("漏洞利用"), XS("Подвиги"));

		LOCALIZATION(aimbot, XS("AIMBOT"), XS("自动瞄准"), XS("АИМБОТ"));
		LOCALIZATION(enable, XS("Enable"), XS("开关"), XS("Бинд на включение"));
		LOCALIZATION(pSilent, XS("pSilent"), XS("沉默"), XS("Невидимый аим"));
		LOCALIZATION(smoothing, XS("Smoothing"), XS("平滑"), XS("Плавность наведения"));
		LOCALIZATION(fovlimit, XS("FOV limit"), XS("自瞄范围"), XS("Радиус аима"));
		LOCALIZATION(prediction, XS("Prediction"), XS("预测"), XS("Упреждение"));
		LOCALIZATION(magic, XS("Magic bullets"), XS("魔法子弹"), XS("Магические пули"));
		LOCALIZATION(magicauto, XS("Magic bullet auto-shoot"), XS("魔法子弹自动射击"), XS("Автоматическая стрельба"));
		LOCALIZATION(magicrapid, XS("Magic bullet rapid-fire"), XS("魔法子弹速射"), XS("Ускоренный темп стрельбы"));
		LOCALIZATION(magicheli, XS("Magic bullet helicopter"), XS("魔弹武装直升机"), XS("Точные попадпния по патрульному вертолёту"));
		LOCALIZATION(magicpoints, XS("Magic bullet points"), XS("魔法点数"), XS("Кол-во точек для сканирования магических пуль"));
		LOCALIZATION(magicstop, XS("Magic auto-stop"), XS("魔法子弹停止"), XS("Автоматическая остановка"));
		LOCALIZATION(magicpos, XS("Shoot at saved position"), XS("在保存的位置拍摄"), XS("Стрелять в сохраненную позицию"));
		LOCALIZATION(pierce, XS("Pierce"), XS("穿"), XS("пронзать"));
		LOCALIZATION(visible, XS("Visible check"), XS("可见检查"), XS("Проверка на видимость"));
		LOCALIZATION(locking, XS("Target locking"), XS("目标锁定"), XS("Привязка к цели"));
		LOCALIZATION(players, XS("Players"), XS("玩家"), XS("Игроки"));
		LOCALIZATION(friends, XS("Friends"), XS("队友"), XS("Тиммейты"));
		LOCALIZATION(npcs, XS("NPCs"), XS("NPC机器人"), XS("НПС"));
		LOCALIZATION(heli, XS("Heli"), XS("直升机"), XS("Вертолёт"));
		LOCALIZATION(hitbox, XS("Hitbox"), XS("命中框"), XS("Место попадания"));
		LOCALIZATION(nospread, XS("No spread"), XS("不扩散"), XS("Отсутствие разброса"));
		LOCALIZATION(nosway, XS("No sway"), XS("没有摇摆"), XS("Нет покачиваний оружия"));
		LOCALIZATION(fasterbullets, XS("Faster bullets"), XS("快速子弹"), XS("ускорение пуль"));
		LOCALIZATION(recoilx, XS("Recoil X"), XS("后坐力 X"), XS("Отдача X"));
		LOCALIZATION(recoily, XS("Recoil Y"), XS("后坐力 Y"), XS("Отдача Y"));
		LOCALIZATION(restrictions, XS("Disable attack restrictions"), XS("禁用攻击限制（可以在驾驶位开枪）"), XS("Стрельба во время прыжков"));
		LOCALIZATION(instanteoka, XS("Instant Eoka"), XS("即时 Eoka"), XS("Быстрая еока"));
		LOCALIZATION(instantcompound, XS("Instant compound bow"), XS("即时复合弓"), XS("Моментальная зарядка блочки"));
		LOCALIZATION(thickness, XS("Bullet thickness"), XS("宽子弹"), XS("Размер пули"));
		LOCALIZATION(adaptivethickness, XS("Adaptive thickness"), XS("自适应厚度"), XS("Адаптивная толщина"));
		LOCALIZATION(ignoreteammates, XS("Ignore damage for teammates"), XS("子弹不会对队友的有伤害"), XS("Игнорирование попадания для тиммейтов"));
		LOCALIZATION(hitoverride, XS("Hit override"), XS("命中覆盖"), XS("Изменение места попадания"));
		LOCALIZATION(helihitoverride, XS("Helicopter hit overide"), XS("直升机的命中覆盖"), XS("Изменение места попадания для вертолёта"));
		LOCALIZATION(automatic, XS("Force automatic"), XS("随机"), XS("Сделать всё оружие автоматическим"));
		LOCALIZATION(head, XS("Head"), XS("头"), XS("Голова"));
		LOCALIZATION(neck, XS("Neck"), XS("脖子"), XS("Шея"));
		LOCALIZATION(chest, XS("Chest"), XS("胸口"), XS("Грудь"));
		LOCALIZATION(lefthand, XS("Left hand"), XS("左手"), XS("левая рука"));
		LOCALIZATION(righthand, XS("Right hand"), XS("右手"), XS("правая рука"));
		LOCALIZATION(random, XS("Random"), XS("随机"), XS("случайный"));
	};
	namespace ESP
	{
		LOCALIZATION(esp, XS("ESP"), XS("玩家绘制"), XS("ЕСП"));
		LOCALIZATION(enabled, XS("Enabled"), XS("开关"), XS("Бинд на включение"));
		LOCALIZATION(focus, XS("Hide on focus"), XS("隐藏焦点"), XS("Скрыть в фокусе"));
		LOCALIZATION(player, XS("Players"), XS("显示玩家"), XS("Игроки"));
		LOCALIZATION(sleeper, XS("Sleepers"), XS("显示躺尸"), XS("Спящие"));
		LOCALIZATION(npc, XS("NPC"), XS("显示NPC"), XS("НПС"));
		LOCALIZATION(box, XS("Box"), XS("显示方框"), XS("Квадрат"));
		LOCALIZATION(skeleton, XS("Skeleton"), XS("显示骨骼"), XS("Скелет"));
		LOCALIZATION(name, XS("Name"), XS("显示名字"), XS("Имя"));
		LOCALIZATION(playerdist, XS("Distance"), XS("显示距离"), XS("Дистанция"));
		LOCALIZATION(health, XS("Health"), XS("显示血条"), XS("Здоровье"));
		LOCALIZATION(flags, XS("Flags"), XS("显示队伍编号"), XS("Индикаторы"));
		LOCALIZATION(teamid, XS("Team ID"), XS("团队标识"), XS("ID команды"));
		LOCALIZATION(activeitem, XS("Active Item"), XS("活动项目"), XS("Предмет в руке"));
		LOCALIZATION(hotbar, XS("Hotbar"), XS("显示快捷栏物品"), XS("Слоты быстрого доступа"));
		LOCALIZATION(chams, XS("Chams"), XS("人物上色"), XS("Слоты"));
		LOCALIZATION(chamswalls, XS("Chams through walls"), XS("人物上色穿墙"), XS("Чамсы сквозь стены"));
		LOCALIZATION(skeletonupdates, XS("Force skeleton updates"), XS("强制骨架更新"), XS("Обновления скелета"));
		LOCALIZATION(skeletondistance, XS("Skeleton update distance"), XS("骨架更新距离"), XS("Расстояние обновления скелета"));
		LOCALIZATION(target, XS("Target"), XS("目标"), XS("Цвет врага"));
		LOCALIZATION(ores, XS("Ores"), XS("矿石"), XS("ЕСП на руды "));
		LOCALIZATION(orestone, XS("Stone##ore"), XS("石头##ore"), XS("Камень##ore"));
		LOCALIZATION(oremetal, XS("Metal##ore"), XS("铁矿##ore"), XS("Металл##ore"));
		LOCALIZATION(oresulfur, XS("Sulfur##ore"), XS("硫磺##ore"), XS("Сера##ore"));
		LOCALIZATION(oredist, XS("Ores distance"), XS("设置距离"), XS("Максимальное расстояние руды"));
		LOCALIZATION(collect, XS("Collectibles"), XS("收藏品"), XS("ЕСП на Собираемые ресурсы"));
		LOCALIZATION(collectdist, XS("Collectibles distance"), XS("收藏品最大距离"), XS("Дистанция собранных ресурсов "));
		LOCALIZATION(fade, XS("Fade"), XS("褪色"), XS("линять"));
		LOCALIZATION(wood, XS("Wood"), XS("木头庄）"), XS("Дерево"));
		LOCALIZATION(stone, XS("Stone"), XS("散落石头"), XS("Камень"));
		LOCALIZATION(sulfur, XS("Sulfur"), XS("散落硫磺"), XS("Сера"));
		LOCALIZATION(metal, XS("Metal"), XS("散落铁矿"), XS("Металл"));
		LOCALIZATION(mushroom, XS("Mushroom"), XS("蘑菇"), XS("Грибы"));
		LOCALIZATION(pumpkin, XS("Pumpkin"), XS("南瓜"), XS("Тыква"));
		LOCALIZATION(corn, XS("Corn"), XS("土豆"), XS("Кукуруза"));
		LOCALIZATION(hemp, XS("Hemp"), XS("布"), XS("Картофель"));
		LOCALIZATION(berry, XS("Berries"), XS("浆果"), XS("Конопля"));
		LOCALIZATION(potato, XS("Potato"), XS("土豆"), XS("Картофель"));
		LOCALIZATION(rad, XS("Radtown"), XS("显示箱子"), XS("РТ ЕСП"));
		LOCALIZATION(raddist, XS("Radtown distance"), XS("最大距离"), XS("РТ ЕСП максимальное расстояние"));
		LOCALIZATION(barrel, XS("Barrels"), XS("桶"), XS("Бочки"));
		LOCALIZATION(crate, XS("Crates"), XS("板条箱"), XS("Ящики"));
		LOCALIZATION(mili, XS("Military crates"), XS("军用板条箱"), XS("Военные ящики"));
		LOCALIZATION(heli, XS("Helicopter crates"), XS("直升机箱"), XS("Ящик для вертолета"));
		LOCALIZATION(elite, XS("Elite crates"), XS("精英板条箱"), XS("Элитные ящики"));
		LOCALIZATION(toolbox, XS("Toolbox"), XS("工具箱"), XS("Ящики"));
		LOCALIZATION(foodbox, XS("Foodbox"), XS("食品盒子"), XS("Ящики с инструментами"));
		LOCALIZATION(otherrad, XS("Other"), XS("其他"), XS("Ящики с едой, остальное"));
		LOCALIZATION(animal, XS("Animals"), XS("显示动物"), XS("ЕСП на животных"));
		LOCALIZATION(animaldist, XS("Animals distance"), XS("动物最大距离"), XS(""));
		LOCALIZATION(bear, XS("Bear"), XS("熊"), XS("Медведь"));
		LOCALIZATION(boar, XS("Boar"), XS("猪"), XS("Кабан"));
		LOCALIZATION(wolf, XS("Wolf"), XS("狼"), XS("Волк"));
		LOCALIZATION(stag, XS("Stag"), XS("鹿"), XS("Олень"));
		LOCALIZATION(stash, XS("Stashes"), XS("小藏匿"), XS("ЕСП на стеши"));
		LOCALIZATION(stashhide, XS("Hide open stashes"), XS("不显示已经打开的小藏匿"), XS("Скрыть открытые тайники"));
		LOCALIZATION(stashdist, XS("Stashes distance"), XS("最大距离"), XS("Максимальное расстояние тайников"));
		LOCALIZATION(raid, XS("Raid ESP"), XS("显示地图爆炸"), XS("ЕСП на рейды"));
		LOCALIZATION(c4, XS("C4"), XS("C4"), XS("С4"));
		LOCALIZATION(satchel, XS("Satchel"), XS("豆罐包"), XS("Сочели"));
		LOCALIZATION(rocket, XS("Rocket"), XS("火箭弹"), XS("Ракеты"));
		LOCALIZATION(incrocket, XS("Incendiary rocket"), XS("燃烧火箭弹"), XS("Зажигательные ракеты"));
		LOCALIZATION(heammo, XS("Explosive ammo"), XS("爆炸子弹"), XS("Разрывные патроны"));
		LOCALIZATION(hegrenade, XS("Explosive grenade"), XS("爆炸手榴弹"), XS("Гранаты"));
		LOCALIZATION(raidstart, XS("Show explosion start timeout"), XS("显示爆炸开始超时"), XS("Время старта рейда"));
		LOCALIZATION(raidlast, XS("Show explosion last timeout"), XS("显示爆炸最后一次超时"), XS("Время со старта рейда"));
		LOCALIZATION(raidtimer, XS("Explosion timer"), XS("爆炸计时器"), XS("Таймер взрыва"));
		LOCALIZATION(raiddist, XS("Raid distance"), XS("显示距离"), XS("Расстояние"));
		LOCALIZATION(other, XS("Other"), XS("其他"), XS("Другой"));
		LOCALIZATION(otherdist, XS("Other distance"), XS("其他最大距离"), XS("Другое максимальное расстояние"));
		LOCALIZATION(airdrop, XS("Airdrop"), XS("空投"), XS("Раздача"));
		LOCALIZATION(vehicle, XS("Vehicles"), XS("显示载具"), XS("ЕСП на технику"));
		LOCALIZATION(mini, XS("Mini"), XS("小型直升机"), XS("Коптер"));
		LOCALIZATION(scrapheli, XS("Scrap Heli"), XS("废料直升机"), XS("Большой вертолёт"));
		LOCALIZATION(helidist, XS("Heli distance"), XS("直升机最大距离"), XS("Максимальное расстояние вертолета"));
		LOCALIZATION(boat, XS("Boats"), XS("船"), XS("Лодки"));
		LOCALIZATION(rhib, XS("RHIBs"), XS("气垫船"), XS("Современные лодки"));
		LOCALIZATION(boatdist, XS("Boats distance"), XS("最大距离"), XS("Максимальное расстояние лодки"));
		LOCALIZATION(horse, XS("Horse"), XS("马"), XS("Лошади"));
		LOCALIZATION(baloon, XS("Hot air baloon"), XS("热气球"), XS("Воздушные шары"));
		LOCALIZATION(othervehdist, XS("Other vehicles distance"), XS("最大距离"), XS("Максимальное расстояние для других транспортных средств"));
		LOCALIZATION(patrol, XS("Patrol helicopter"), XS("巡逻直升机"), XS("Патрульный вертолёт"));
		LOCALIZATION(bradley, XS("Bradley"), XS("布拉德利"), XS("Танк"));
		LOCALIZATION(trap, XS("Traps"), XS("显示陷阱"), XS("ЕСП на ловушки"));
		LOCALIZATION(traphide, XS("Hide innactive traps"), XS("隐藏无效的陷阱"), XS("Отфильтрововать отключённые ловушки"));
		LOCALIZATION(trapdist, XS("Traps distance"), XS("最大距离"), XS("Максимальное расстояние ловушек"));
		LOCALIZATION(turret, XS("Auto turrets"), XS("自动炮塔（友好+敌人颜色）"), XS("Турели"));
		LOCALIZATION(turretauth, XS("Authed Auto Turrets"), XS("已授权的炮塔"), XS("Авторизованные автоматические турели"));
		LOCALIZATION(turrethide, XS("Hide Authed Auto Turrets"), XS("隐藏授权的自动炮塔"), XS("Скрыть авторизованные автоматические турели"));
		LOCALIZATION(samsite, XS("SAM sites"), XS("防空炮"), XS("ПВО"));
		LOCALIZATION(shotguntrap, XS("Shotgun traps"), XS("霰弹枪陷阱"), XS("Гантрап"));
		LOCALIZATION(flameturret, XS("Flame Turrets "), XS("火焰炮塔"), XS("Огнемётная ловушка"));
		LOCALIZATION(landmine, XS("Land mines"), XS("地雷"), XS("Мины"));
		LOCALIZATION(beartrap, XS("Bear traps"), XS("熊陷阱"), XS("Капканы"));
		LOCALIZATION(droppable, XS("Droppables"), XS("掉落物品"), XS("ЕСП на вещи"));
		LOCALIZATION(itemdist, XS("Item distance"), XS("最大距离"), XS("Максимальное расстояние предметов"));
		LOCALIZATION(backpack, XS("Backpacks"), XS("尸体包"), XS("Рюкзаки"));
		LOCALIZATION(backpackdist, XS("Backpacks distance"), XS("尸体包最大距离"), XS("Максимальное расстояние между рюкзаками игрока"));
		LOCALIZATION(corpse, XS("Corpse"), XS("尸体"), XS("Трупы"));
		LOCALIZATION(corpsename, XS("Corpse name"), XS("尸体名称"), XS("Имя трупа"));
		LOCALIZATION(corpsedist, XS("Corpse distance"), XS("尸体最大距离"), XS("Максимальное расстояние до трупа"));
		LOCALIZATION(bag, XS("Sleeping Bags"), XS("显示睡袋"), XS("ЕСП на Спалки"));
		LOCALIZATION(bagname, XS("Sleeping bag name"), XS("睡袋名称"), XS("Название спального мешка"));
		LOCALIZATION(bagdist, XS("Sleeping bag distance"), XS("睡袋最大距离"), XS("Максимальное расстояние спального мешка"));
		LOCALIZATION(tc, XS("Tool cupboard"), XS("显示领地柜"), XS("ЕСП на шкафы"));
		LOCALIZATION(tcdecay, XS("Show only decaying "), XS("只显示衰减"), XS("Показывать только гниющие шкафы"));
		LOCALIZATION(tclist, XS("Tool cupboard list"), XS("领地柜授权人员"), XS("Показывать авторизированных игроков"));
		LOCALIZATION(tcfov, XS("Tool cupboard list FOV"), XS("领地柜列表 FOV"), XS("Список шкафов для инструментов FOV"));
		LOCALIZATION(tcdistance, XS("Tool cupboard distance"), XS("领地柜距离"), XS("Расстояние до шкафа для инструментов"));
		LOCALIZATION(wb, XS("Workbench"), XS("工作台"), XS("ЕСП на Верстак"));
		LOCALIZATION(wbmax, XS("Workbench lvl 3 only"), XS("仅工作台 LVL 3"), XS("Только верстак LVL 3"));
		LOCALIZATION(wbdist, XS("Workbench distance"), XS("工作台距离"), XS("Расстояние до верстака"));
		LOCALIZATION(radar, XS("Radar"), XS("雷达"), XS("Радар"));
		LOCALIZATION(radarenemy, XS("Enemies"), XS("敌人"), XS("Врагов"));
		LOCALIZATION(radarteam, XS("Teammates"), XS("队友"), XS("Команде"));
		LOCALIZATION(radarwound, XS("Wounded players"), XS("受伤的球员"), XS("Раненые игроки"));
		LOCALIZATION(radarsleep, XS("Sleepers"), XS("枕木"), XS("Шпалы"));
		LOCALIZATION(radarnpc, XS("NPCs"), XS("全国人大"), XS("Неигровики"));
		LOCALIZATION(crosshair, XS("Crosshair"), XS("准星"), XS("Прицел"));
		LOCALIZATION(watermark, XS("Watermark"), XS("水印"), XS("Вотермарк"));
		LOCALIZATION(point, XS("Aimbot point"), XS("瞄准点"), XS("Точка цели аима"));
		LOCALIZATION(drawFOV, XS("Draw FOV"), XS("绘制视野"), XS("Нарисовать поле зрения"));
		LOCALIZATION(visualPrediction, XS("Visual prediction"), XS("绘制火箭土地"), XS("Нарисуйте ракетную землю"));
		LOCALIZATION(muzzleToTarget, XS("Muzzle point to target"), XS("枪口指向目标 "), XS("Прицел на цель"));
		LOCALIZATION(markCamera, XS("Mark camera position"), XS("标记相机位置"), XS("Отметить положение камеры"));
		LOCALIZATION(chamstype, XS("Chams type"), XS("查姆斯类型"), XS("Тип Слоты"));
		LOCALIZATION(chamsglow, XS("Glow"), XS("辉光"), XS("Светиться"));
		LOCALIZATION(chamsoutline, XS("Outline"), XS("大纲"), XS("Контур"));
		LOCALIZATION(chamsdefault, XS("Default"), XS("缺省"), XS("Дефолт"));
		LOCALIZATION(chamstime, XS("Time multiplier"), XS("时间乘数"), XS("Множитель времени"));
		LOCALIZATION(chamsintensity, XS("Intensity"), XS("强度"), XS("Интенсивность"));
		LOCALIZATION(chamsthickness, XS("Thickness"), XS("厚度"), XS("Толщина"));
		LOCALIZATION(saveshootpos, XS("Saved shoot position"), XS("保存的拍摄位置"), XS("Сохраненная позиция стрельбы"));
	};
	namespace MISC
	{
		LOCALIZATION(enable, XS("Enable misc processing"), XS("使能够杂项"), XS("Включить дополнительный функционал"));
		LOCALIZATION(misc, XS("MISC"), XS("杂项"), XS("ДОПОЛНИТЕЛЬНОЕ"));
		LOCALIZATION(movement, XS("Movement"), XS("移动"), XS("Двигательные"));
		LOCALIZATION(visual, XS("Visual"), XS("视觉效果"), XS("Двигательные"));
		LOCALIZATION(spider, XS("Spiderman"), XS("爬墙"), XS("Цепляние к стенам"));
		LOCALIZATION(jump, XS("Infinite jump"), XS("无限跳跃"), XS("Неограниченные прыжки"));
		LOCALIZATION(jesus, XS("Jesus"), XS("水上行走"), XS("Хождение по воде"));
		LOCALIZATION(treecollision, XS("Ignore tree collision"), XS("忽略树碰撞"), XS("Проход сквозь дереевья"));
		LOCALIZATION(omni, XS("Omni-sprint"), XS("全方位冲刺"), XS("Спринт везде"));
		LOCALIZATION(walk, XS("Silent walk"), XS("消除走路声音"), XS("Бесшумное хождение"));
		LOCALIZATION(flyhack, XS("Flyhack"), XS("飞天"), XS("Полёт"));
		LOCALIZATION(flyhackspeed, XS("Flyhack speed "), XS("飞天速度设置"), XS("Скорость Flyhack"));
		LOCALIZATION(noclip, XS("No flyhack collider"), XS("没有飞黑客对撞机"), XS("Полёт без коллизии"));
		LOCALIZATION(antikick, XS("Anti-kick"), XS("防踢"), XS("Анти-Кик система"));
		LOCALIZATION(absolute, XS("Absolute"), XS("绝对"), XS("Абсолютный"));
		LOCALIZATION(phase, XS("Phase"), XS("阶段"), XS("Небольшой телепорт"));
		LOCALIZATION(phasedist, XS("Phase distance"), XS("相位距离"), XS("Фазовое расстояние"));
		LOCALIZATION(giraffe, XS("Giraffe"), XS("长脖子"), XS("Длинная шея"));
		LOCALIZATION(giraffeheight, XS("Giraffe height"), XS("设置长脖子高度"), XS("Высота жирафа"));
		LOCALIZATION(player, XS("Player"), XS("播放"), XS("Игрока"));
		LOCALIZATION(admin, XS("Admin flag "), XS("管理员权限"), XS("Админские полномочия"));
		LOCALIZATION(mounted, XS("Equip items while mounted"), XS("可以在任何地方开枪"), XS("Можно брать в руки предметы сидя на чём-то"));
		LOCALIZATION(nofall, XS("No fall damage"), XS("无坠落伤害"), XS("Нет урона от падения"));
		LOCALIZATION(revive, XS("Instant revive"), XS("即时复活"), XS("Моментальное поднятие"));
		LOCALIZATION(med, XS("Instant med"), XS("即时药物"), XS("Моментальное леечение"));
		LOCALIZATION(tick, XS("Tick interval"), XS("滴答间隔"), XS("Фейклаги"));
		LOCALIZATION(antiaim, XS("Anti-aim"), XS("摇头"), XS("Крутилка"));
		LOCALIZATION(whitelist, XS("Whitelist player"), XS("白名单玩家"), XS("Пометить игрока как друга"));
		LOCALIZATION(other, XS("Other"), XS("其他"), XS("ОСТАЛЬНОЕ"));
		LOCALIZATION(loot, XS("Instant loot"), XS("快速拾取战利品"), XS("Моментальный перенос предметов"));
		LOCALIZATION(spam, XS("Weapon spam"), XS("武器垃圾邮件"), XS("Спам выстрелами"));
		LOCALIZATION(melee, XS("Silent melee"), XS("静默攻击（手持工具）"), XS("Удары без анимаций"));
		LOCALIZATION(farm, XS("Silent farm"), XS("自动抛矿和树"), XS("Автоматический фарм"));
		LOCALIZATION(collect, XS("Auto collect"), XS("自动收集"), XS("Авто подбор"));
		LOCALIZATION(brightcave, XS("Bright cave"), XS("明亮的洞穴"), XS("Светло в пещерах"));
		LOCALIZATION(brightnight, XS("Bright night"), XS("明亮的夜晚"), XS("Яркость ночи"));
		LOCALIZATION(brightness, XS("Brightness"), XS("亮度"), XS("Можно настроить яркость"));
		LOCALIZATION(debug, XS("Interactive debug"), XS("交互式调试"), XS("Телепорт игрока в пределах возможного"));
		LOCALIZATION(floorstack, XS("Floor-stack assist"), XS("地板堆叠辅助"), XS("Стакать структуры"));
		LOCALIZATION(floorstackheight, XS("Floorstack height difference"), XS("地板高度差"), XS("Разница высот между структурами"));
		LOCALIZATION(rotation, XS("Rotation offset"), XS("旋转偏移"), XS("Градус поворота"));
		LOCALIZATION(rotate, XS("Rotate block"), XS("旋转块"), XS("Поворот структур"));
		LOCALIZATION(zoom, XS("Zoom Hack"), XS("视野放大"), XS("Увеличенное прицеливание"));
		LOCALIZATION(zoomamount, XS("Zoom Hack Amount"), XS("视野放大设置值"), XS("Сумма увеличения"));
		LOCALIZATION(fov, XS("FOV Changer"), XS("视角FOV （默认90）"), XS("Изменение угла обзора"));
		LOCALIZATION(attire, XS("Hide Attire Overlays"), XS("隐藏服装叠加"), XS("Улучшить обзор в Джаггер-Сете"));
		LOCALIZATION(playerlist, XS("Player list"), XS("球员名单"), XS("Список игроков"));
		LOCALIZATION(language, XS("Language"), XS("语言"), XS("Язык"));
		LOCALIZATION(autoupg, XS("Auto upgrade"), XS("自动升级"), XS("Автообновление"));
		LOCALIZATION(autoupggrade, XS("Auto upgrade grade"), XS("自动升级等级"), XS("Оценка автообновления"));
		LOCALIZATION(autoupgonlytwig, XS("Auto upgrade only twig"), XS("自动升级只有树枝"), XS("Автообновление только веточки"));
		LOCALIZATION(twig, XS("Twig"), XS("枝条"), XS("Веточка"));
		LOCALIZATION(hqmetal, XS("High-quality metal"), XS("高品质金属"), XS("Качественный металл"));
	};
	namespace PLAYERLIST
	{
		LOCALIZATION(list, XS("PLAYER LIST"), XS("球员名单"), XS("СПИСОК ИГРОКОВ"));
		LOCALIZATION(name, XS("NAME"), XS("姓名"), XS("ИМЯ"));
	};
	namespace TAB
	{
		LOCALIZATION(aimbot, XS("Aimbot"), XS("瞄准器"), "");
		LOCALIZATION(visuals, XS("Visuals"), XS("视觉效果"), "");
		LOCALIZATION(misc, XS("Misc"), XS("各种各样的"), "");
		LOCALIZATION(player, XS("Players"), XS("球员"), "");
		LOCALIZATION(config, XS("Config"), XS("配置"), "");
	};
	namespace CONFIG
	{
		LOCALIZATION(save, XS("Save config"), XS("保存配置"), "");
		LOCALIZATION(load, XS("Load config"), XS("加载配置"), "");
		LOCALIZATION(init, XS("Register config"), XS("创建配置"), "");
	};
};
