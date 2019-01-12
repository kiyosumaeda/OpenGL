#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//ウィンドウ関連の処理
class Window {
    //ウィンドウのハンドル
    GLFWwindow *const window;
    
public:
    
    //コンストラクタ
    Window(int width = 640, int height = 480, const char *title = "Hello!")
    : window(glfwCreateWindow(width, height, title, NULL, NULL)) {
        if (window == NULL) {
            //ウィンドウが作成できなかった
            std::cerr << "Can't create GLFW window." << std::endl;
            exit(1);
        }
        
        //現在のウィンドを処理対象にする
        glfwMakeContextCurrent(window);
        
        //GLEWを初期化する
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            //GLEWの初期化に失敗した
            std::cerr << "Can't initialize GLEW" << std::endl;
            exit(1);
        }
        
        //垂直同期のタイミングを待つ
        glfwSwapInterval(1);
        
        //ウィンドウのサイズ変更時に呼び出す処理の登録
        glfwSetWindowSizeCallback(window, resize);
        
        //開いたウィンドの初期設定
        resize(window, width, height);
    }
    
    //デストラクタ
    virtual ~Window() {
        glfwDestroyWindow(window);
    }
    
    //ウィンドを閉じるべきかを判定する
    int shouldClose() const {
        return glfwWindowShouldClose(window);
    }
    
    //カラーバッファを入れ替えてイベントを取り出す
    void swapBuffers() {
        //カラーバッファを入れ替える
        glfwSwapBuffers(window);
        
        //イベントを取り出す
        glfwWaitEvents();
    }
    
    static void resize(GLFWwindow *const window, int width, int height) {
        //ウィンドウ全体をビューポートに設定する
        glViewport(0, 0, width, height);
    }
};
