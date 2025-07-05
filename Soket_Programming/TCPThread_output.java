import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class TCPThread_output extends Thread{

    private Socket socket;
    private PrintWriter pw = null;
    private String userIP;
    private BufferedReader inFromUser;
    volatile boolean terminationFlag = true;

    TCPThread_output(Socket s)
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
        inFromUser = new BufferedReader(new InputStreamReader(System.in)); //입력 버퍼 생성, 터미널 입력과 연결
        pw = new PrintWriter(socket.getOutputStream(), true); //상대에게 전달할 출력 버퍼 생성
        String str = null;

        while(terminationFlag) {
            str = inFromUser.readLine(); // 입력 버퍼로부터 한 줄 읽기
            if (str != null && str.equals("end"))
            {
                pw.println("end");
                break;  //다 읽었으면 반복문 탈출
            }
            else if (str != null)
                pw.println(str);
        }
        System.out.println(userIP + " : Output Completed");
    }

    private void closeAll() throws IOException
    {
        if (pw != null)
            pw.close();
        if (socket != null)
            socket.close();
    }

    public void stopThread() {
        terminationFlag = false;
    }
}