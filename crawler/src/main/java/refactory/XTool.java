package refactory;

import org.jsoup.nodes.Element;

import java.io.InputStream;
import java.io.InputStreamReader;

/**
 * Created with IntelliJ IDEA.
 * User: houming
 * Date: 6/4/13
 * Time: 6:17 PM
 * To change this template use File | Settings | File Templates.
 */
public class XTool {

  public static void printElementStrings(Element element) {
    System.out.println("nodeName:" + element.nodeName());
    System.out.println("tagName:" + element.tagName());
    System.out.println("id:" + element.id());
    System.out.println("text:" + element.text());
    System.out.println("ownText:" + element.ownText());
    System.out.println("data:"+ element.data());
    System.out.println("val:" + element.val());
    System.out.println("toString:" + element.toString());
  }

  static public String getString(InputStream stream){
    try {
      InputStreamReader isr = new InputStreamReader(stream);
      System.out.println("stream charset:"+isr.getEncoding());
      BufferedReader br = new BufferedReader(isr);
      StringBuilder sb = new StringBuilder();
      String tmp = br.readLine();
      while(tmp != null){
        sb.append(tmp);
        sb.append("\n");
        tmp = br.readLine();
      }
      return sb.toString();
    } catch (IOException e) {
      e.printStackTrace();
      return null;
    }
  }

  static public String getString(InputStream stream,String charset){
    StringBuilder sb = new StringBuilder();
    try {
      InputStreamReader isr = new InputStreamReader(stream,charset);
      BufferedReader br = new BufferedReader(isr);
      String tmp = br.readLine();
      while(tmp != null){
        sb.append(tmp);
        sb.append("\n");
        tmp = br.readLine();
      }
      return sb.toString();
    } catch (IOException e) {
      e.printStackTrace();
      return sb.toString();
    }
  }
}
