// 메모리 문제를 해결하라
// 1 - 2 - 3 형태의 Node list 만들고 출력하라.
// 특정 노드의 next, previous 가 존재하는지 여부를 확인하세요.

#include <iostream>
#include <memory>

class Node {
    int data = 0;
public:
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> previous;
    Node(int n) : data(n) {}
    ~Node() { std::cout << "Node destroyed" << std::endl; }
    void PrintNode() { std::cout << data << " "; }

};

int main() {
    std::shared_ptr<Node> node = std::make_shared<Node>(0);
    if(node.get()) node->PrintNode();

    std::shared_ptr<Node> node1 = std::make_shared<Node>(1);
    std::shared_ptr<Node> node2 = std::make_shared<Node>(2);

    node1->next = node2;        // node1이 node2를 가리킴
    node2->previous = node1;    // node2가 node1을 가리킴 (순환 참조 발생)
        

    // 이 상태에서 두 노드는 서로를 참조하고 있기 때문에 소멸되지 않음
    return 0;  // 메모리 누수 발생
}


/*
#include <iostream>
#include <memory>

class Node {
public:
    std::shared_ptr<Node> next;         // 다음 노드를 가리키는 shared_ptr
    std::weak_ptr<Node> previous;       // 이전 노드를 가리키는 weak_ptr (순환 참조 방지)

    ~Node() {
        std::cout << "Node destroyed" << std::endl;
    }
};

int main() {
    // 두 개의 노드를 생성
    std::shared_ptr<Node> node1 = std::make_shared<Node>();
    std::shared_ptr<Node> node2 = std::make_shared<Node>();

    // 순환 참조 설정
    node1->next = node2;                // node1이 node2를 가리킴 (shared_ptr)
    node2->previous = node1;            // node2가 node1을 가리킴 (weak_ptr)

    // weak_ptr을 shared_ptr로 변환할 때 lock()을 사용하여 안전하게 접근
    if (auto prev = node2->previous.lock()) {
        std::cout << "Node2 has a previous node." << std::endl;
    } else {
        std::cout << "Node2 has no previous node." << std::endl;
    }

    // 프로그램 종료 시 노드들이 올바르게 소멸됨
    return 0;
}

*/