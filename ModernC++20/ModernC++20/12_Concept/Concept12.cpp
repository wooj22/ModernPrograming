//게임 엔진 스타일 문제 : concept + DI 설계

//문제. 다음 조건을 만족하는 컴포넌트 시스템을 설계하시오.
//설계 목표 :
//	컴포넌트는 인터페이스(기능) 기반으로 동작
//	컴포넌트를 template으로 주입받되, 필요한 기능을 concept으로 제한
//	런타임이 아닌 컴파일 타임에서 타입 불일치 감지
//	예 : Renderable, Updatable, PhysicsComponent 등 역할 분리
//	의존성은 생성자 인젝션(template DI) 형태로 주입

#include <concepts>
#include <iostream>

//개념 정의 (Concepts)

template<typename T>
concept Renderable = requires(T t) {
    { t.render() } -> std::same_as<void>;
};

template<typename T>
concept Updatable = requires(T t, float dt) {
    { t.update(dt) } -> std::same_as<void>;
};

//컴포넌트 설계 (DI 형태)

template<Renderable R, Updatable U>
class GameEntity {
public:
    GameEntity(R r, U u) : renderer(r), updater(u) {}

    void update(float dt) {
        updater.update(dt);
    }

    void render() {
        renderer.render();
    }

private:
    R renderer;
    U updater;
};

//구현 예시 : Renderer, Updater

struct SpriteRenderer {
    void render() {
        std::cout << "[SpriteRenderer] rendering\n";
    }
};

struct AIController {
    void update(float dt) {
        std::cout << "[AIController] updating with dt=" << dt << "\n";
    }
};

int main() {
    SpriteRenderer sr;
    AIController ai;

    GameEntity entity(sr, ai);
    entity.update(0.016f);
    entity.render();
}