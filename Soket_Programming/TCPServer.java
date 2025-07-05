import java.io.*;
import java.net.*;

class TCPServer {

    public void go() throws IOException
    {
        ServerSocket serverSocket = null;     // client socket 받기용 serversocket 생성
        Socket s = null;                      // 임시저장용 soket

        try {
            serverSocket =  new ServerSocket(6789);  //binding
            System.out.println("ServerSocket is binded");

            while(true)
            {
                System.out.println("\nconnecting...\n");
                s = serverSocket.accept();                                 // client socket 연결 대기...
                System.out.println(s.getInetAddress() + " is connected!");
                TCPThread_input input = new TCPThread_input(s);
                TCPThread_output output = new TCPThread_output(s);       // 연결 성공하면 TCPThread class 생성
                 try {
                    input.start(); //thread start
                    output.start();
                    input.join();
                    if (input.isAlive() == false) {  //만약 Client 측에서 종료 요청이 왔다면,
                        output.stopThread();          // outthread를 종료시킨다.
                    }
                }
                catch(InterruptedException e)
                {
                   e.printStackTrace();
                }
            }
        }
        finally
        {
            if (s != null)
                s.close();
            if (serverSocket != null)
                serverSocket.close();
        }
    } 

    public static void main(String argv[]) throws Exception
    {
        TCPServer server = new TCPServer(); //server class 생성
        try {
            server.go();                    //server.go()함수 실행
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}