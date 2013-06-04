package core.test;

import core.AppConfig;
import org.apache.http.HttpEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClientBuilder;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import refactory.Api;

import java.io.IOException;
import java.io.InputStream;
import java.util.Scanner;
import java.util.Set;

/**
 * Created with IntelliJ IDEA.
 * User: houming
 * Date: 6/4/13
 * Time: 2:46 PM
 * To change this template use File | Settings | File Templates.
 */
@RunWith(JUnit4.class)
public class Main {

  @Test
  public void one() throws IOException {
    AppConfig conf = AppConfig.getInstance();
    HttpClientBuilder builder = HttpClientBuilder.create();
    CloseableHttpClient client = builder.build();
    HttpGet httpget = new HttpGet("http://weibo.com/");
    CloseableHttpResponse resp = client.execute(httpget);
    HttpEntity respEntity = resp.getEntity();
    InputStream inputStream = respEntity.getContent();
    Scanner scanner = new Scanner(inputStream);
    String all = scanner.toString();
    StringBuilder sb = new StringBuilder();
    while(scanner.hasNext()) {
    sb.append(scanner.nextLine()+"\n");
    }
    Set links = Api.getLinksSet(sb.toString());
    httpget.releaseConnection();
  }

  @Test
  public void two() throws IOException {
    AppConfig conf = AppConfig.getInstance();
    HttpClientBuilder builder = HttpClientBuilder.create();
    CloseableHttpClient client = builder.build();
    HttpGet httpget = new HttpGet("http://weibo.com/");
    CloseableHttpResponse resp = client.execute(httpget);
    HttpEntity respEntity = resp.getEntity();
    InputStream inputStream = respEntity.getContent();
    Scanner scanner = new Scanner(inputStream);
    String all = scanner.toString();
    StringBuilder sb = new StringBuilder();
    while(scanner.hasNext()) {
      sb.append(scanner.nextLine()+"\n");
    }
    Set links = Api.getLinksSet(sb.toString());
    httpget.releaseConnection();
  }
}
