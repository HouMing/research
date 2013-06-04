package refactory;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.util.Set;
import java.util.TreeSet;

/**
 * Created with IntelliJ IDEA.
 * User: houming
 * Date: 6/4/13
 * Time: 4:48 PM
 * To change this template use File | Settings | File Templates.
 */
public class Api {

  public static Set<String> getLinksSet(String url) {
    Document doc = Jsoup.parse(url);
    TreeSet<String> ret = new TreeSet<String>();
    Elements allElements = doc.getAllElements();
    for (int  i = 0; i< allElements.size(); i++) {
      Element element = allElements.get(i);
      if (element.tagName().equals("a")) {
        ret.add(element.attr("href"));
      }
    }
    return ret;
  }

}
