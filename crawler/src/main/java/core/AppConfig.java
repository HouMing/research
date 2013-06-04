package core;

/**
 * Created with IntelliJ IDEA.
 * User: houming
 * Date: 6/4/13
 * Time: 4:00 PM
 * To change this template use File | Settings | File Templates.
 */
public class AppConfig {
  String userName;
  String password;
  boolean inited = false;
  private static AppConfig instance;

  private AppConfig() {
  }

  public static AppConfig getInstance() {
    if (instance == null) {
      instance = new AppConfig();
    }
    if (instance.inited == false) {
      instance.userName = "56071912@qq.com";
      instance.password = "112233hou";
      instance.inited = true;
    }
    return instance;
  }
}
