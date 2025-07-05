import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class TCPThread_input extends Thread{

    private Socket socket;
    private BufferedReader br = null;
    private String userIP;
    volatile boolean terminationFlag = true;

    TCPThread_input(Socket s)
    {
        this.socket = s;
        userIP = socket.getInetAddress().toString();
    }

    public void run()  //st.start() 함수에 의해 실행, Thread.run()
    {
        try
        {
            service(); // service() 실행
        }
        catch(IOException e)
        {
            System.out.println(userIP  + "IOException in run");
        }
        finally
        {
            try
            {
                closeAll(); //생성된 입출력 버퍼, socket 닫기

            } catch (Exception e) {
               e.printStackTrace();
            }
        }
    }

    private void service() throws IOException
    {
        br = new BufferedReader(new InputStreamReader(socket.getInputStream())); //상대로부터 입력받을 버퍼 생성
        String str = null;

        while(terminationFlag) {
            str = br.readLine(); // 입력 버퍼로부터 한 줄 읽기
            if (str != null && str.equals("end"))
            {
                break;  //다 읽었으면 반복문 탈출
            }
            else if (str != null)
                System.out.println(userIP + " : " + str); //상대가 입력한 내용 출력
        }
         System.out.println(userIP + " : Input Completed");
    }

    private void closeAll() throws IOException
    {
        if (br != null)
            br.close();
        if (socket != null)
            socket.close();
    }

     public void stopThread() {
        terminationFlag = false;
    }
}