import java.io.*;
import java.net.*;

class TCPClient {

    public void go() throws IOException
    {
        Socket clientSocket = null;
        
        try {
            clientSocket = new Socket("localhost", 6789); // 포트 6789로 host와 연결된 socket 생성     
            
            TCPThread_input input = new TCPThread_input(clientSocket);
            TCPThread_output output = new TCPThread_output(clientSocket);
            try {
                    input.start();
                    output.start();
                    output.join();
                    if (output.isAlive() == false) {  //만약 Client 측에서 종료 요청 했다면,
                        input.stopThread();           //input thread도 종료시킨다.
                    }
                    input.join();
                    if (input.isAlive() == false) {  //만약 Server 측에서 종료 요청이 왔다면,
                        output.stopThread();          // outthread를 종료시킨다.
                    }
                }
                catch(InterruptedException e)
                {
                   e.printStackTrace();
                }
        }
        finally
        {
            if (clientSocket != null)
                clientSocket.close();
        }
    }

    public static void main(String argv[]) throws Exception
    {
        TCPClient client = new TCPClient();
        try{
            client.go();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}