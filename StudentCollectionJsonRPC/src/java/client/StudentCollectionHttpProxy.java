package sample.student.client;

import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;
import java.util.zip.GZIPInputStream;
import java.util.ArrayList;
import java.util.Arrays;
import org.json.JSONObject;
import org.json.JSONArray;

/**
 * Copyright (c) 2020 Tim Lindquist,
 * Software Engineering,
 * Arizona State University at the Polytechnic campus
 * <p/>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 * <p/>
 * This program is distributed in the hope that it will be useful,
 * but without any warranty or fitness for a particular purpose.
 * <p/>
 * Please review the GNU General Public License at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 * see also: https://www.gnu.org/licenses/gpl-faq.html
 * so you are aware of the terms and your rights with regard to this software.
 * Or, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 * <p/>
 * Purpose:
 * A Java class demonstrating a client side proxy class manually created to implement
 * JsonRpc methods where argument and return types are user-defined classes.
 *
 * @author Tim Lindquist (tim.lindquist@asu.edu), ASU Software Engineering
 * @version April 2020
 * @license See above
 */
public class StudentCollectionHttpProxy {

   static final boolean debugOn = false;
   private final Map<String, String> headers;
   private URL url;
   private String requestData;
   private static int callid =0;

   public StudentCollectionHttpProxy(URL url) {
      this.url = url;
      this.headers = new HashMap<String, String>();
   }

   private JSONObject buildCall(String method){
      JSONObject jobj = new JSONObject("{\"jsonrpc\":\"2.0\",\"method\":\""+method+"\",\"id\":"+callid+"}");
      return jobj;
   }

   //Methods recognized by the server
   /*
    *saveToJsonFile()-->boolean
    */
   public boolean saveToJsonFile(){
      boolean ret = false;
      try{
         JSONObject jobj = this.buildCall("saveToJsonFile");
         JSONArray params = new JSONArray();
         jobj.put("params",params);
         String request = jobj.toString();
         String response = this.call(request);
         debug("getNames returned: "+response);
         JSONObject respObj = new JSONObject(response);
         if(!respObj.has("error")){
            ret = respObj.optBoolean("result");
         }
      }catch(Exception ex){
         System.out.println("exception in resetFromJsonFile error: "+ex.getMessage());
      }
      return ret;
   }

   /*
    *resetFromJsonFile()-->boolean
    */
   public boolean resetFromJsonFile(){
      boolean ret = false;
      try{
         JSONObject jobj = this.buildCall("resetFromJsonFile");
         JSONArray params = new JSONArray();
         jobj.put("params",params);
         String request = jobj.toString();
         String response = this.call(request);
         debug("getNames returned: "+response);
         JSONObject respObj = new JSONObject(response);
         if(!respObj.has("error")){
            ret = respObj.optBoolean("result");
         }
      }catch(Exception ex){
         System.out.println("exception in resetFromJsonFile error: "+ex.getMessage());
      }
      return ret;
   }

   /*
    *add(Student aStudent)-->boolean
    */
   public boolean add(Student aStudent){
      boolean ret = false;
      try{
         JSONObject jobj = this.buildCall("add");
         JSONArray params = new JSONArray();
         params.put(aStudent.toJson());
         jobj.put("params",params);
         String request = jobj.toString();
         String response = this.call(request);
         debug("add returned: "+response);
      }catch(Exception ex){
         System.out.println("exception in add "+aStudent.toJsonString()+" error: "+ex.getMessage());
      }
      return ret;
   }

   /*
    *remove(String aStudentName)-->boolean
    */
   public boolean remove(String aStudentName){
      boolean ret = false;
      try{
         JSONObject jobj = this.buildCall("remove");
         JSONArray params = new JSONArray();
         params.put(aStudentName);
         jobj.put("params",params);
         String request = jobj.toString();
         String response = this.call(request);
         debug("remove returned: "+response);
         JSONObject respObj = new JSONObject(response);
         if(!respObj.has("error")){
            ret = respObj.optBoolean("result");
         }
      }catch(Exception ex){
         System.out.println("exception in remove "+aStudentName+" error: "+ex.getMessage());
      }
      return ret;
   }

   /*
    *get(String aStudentName)-->Student
    */
   public Student get(String aStudentName){
      Student ret = new Student("unknown",999,new String[]{"Ser321"});
      try{
         JSONObject jobj = this.buildCall("get");
         JSONArray params = new JSONArray();
         params.put(aStudentName);
         jobj.put("params",params);
         String request = jobj.toString();
         String response = this.call(request);
         debug("remove returned: "+response);
         JSONObject respObj = new JSONObject(response);
         if(!respObj.has("error")){
            JSONObject obj = respObj.optJSONObject("result");
            ret = new Student(obj);
         }
      }catch(Exception ex){
         System.out.println("exception in get "+aStudentName+" error: "+ex.getMessage());
      }
      return ret;
   }

   /*
    *getNames()-->String[]
    */
   public String[] getNames(){
      String[] ret = new String[]{};
      try{
         JSONObject jobj = this.buildCall("getNames");
         JSONArray params = new JSONArray();
         jobj.put("params",params);
         String request = jobj.toString();
         String response = this.call(request);
         debug("getNames returned: "+response);
         JSONObject respObj = new JSONObject(response);
         if(!respObj.has("error")){
            ArrayList<String> al = new ArrayList<String>();
            JSONArray ja = respObj.optJSONArray("result");
            for(int i=0; i<ja.length(); i++){
               String aName = ja.optString(i);
               if(aName!=""){
                  al.add(aName);
               }
            }
            ret = al.toArray(new String[]{});
            Arrays.sort(ret);
         }
      }catch(Exception ex){
         System.out.println("exception in getNames error: "+ex.getMessage());
      }
      return ret;
   }

   /*
    *getById(int id)-->String
    */
   public String getById(int id){
      String ret = "unknown";
      try{
         JSONObject jobj = this.buildCall("getById");
         JSONArray params = new JSONArray();
         params.put(id);
         jobj.put("params",params);
         String request = jobj.toString();
         String response = this.call(request);
         debug("remove returned: "+response);
         JSONObject respObj = new JSONObject(response);
         if(!respObj.has("error")){
            ret = respObj.optString("result");
         }
      }catch(Exception ex){
         System.out.println("exception in getById "+id+", error: "+ex.getMessage());
      }
      return ret;
   }

   public void setHeader(String key, String value) {
      this.headers.put(key, value);
   }

   public String call(String requestData) throws Exception {
      debug("in call, url: "+url.toString()+" requestData: "+requestData);
      String respData = post(url, headers, requestData);
      return respData;
   }

   private String post(URL url, Map<String, String> headers, String data) throws Exception {
      HttpURLConnection connection = (HttpURLConnection) url.openConnection();
      this.requestData = data;
      if (headers != null) {
         for (Map.Entry<String, String> entry : headers.entrySet()) {
            connection.addRequestProperty(entry.getKey(), entry.getValue());
         }
      }
      connection.addRequestProperty("Accept-Encoding", "gzip");
      connection.setRequestMethod("POST");
      connection.setDoOutput(true);
      connection.connect();
      OutputStream out = null;
      try {
         out = connection.getOutputStream();
         out.write(data.getBytes());
         out.flush();
         out.close();
         int statusCode = connection.getResponseCode();
         if (statusCode != HttpURLConnection.HTTP_OK) {
            throw new Exception(
               "Unexpected status from post: " + statusCode);
         }
      } finally {
         if (out != null) {
            out.close();
         }
      }
      String responseEncoding = connection.getHeaderField("Content-Encoding");
      responseEncoding = (responseEncoding == null ? "" : responseEncoding.trim());
      ByteArrayOutputStream bos = new ByteArrayOutputStream();
      InputStream in = connection.getInputStream();
      try {
         in = connection.getInputStream();
         if ("gzip".equalsIgnoreCase(responseEncoding)) {
            in = new GZIPInputStream(in);
         }
         in = new BufferedInputStream(in);
         byte[] buff = new byte[1024];
         int n;
         while ((n = in.read(buff)) > 0) {
            bos.write(buff, 0, n);
         }
         bos.flush();
         bos.close();
      } finally {
         if (in != null) {
            in.close();
         }
      }
      debug("post: json rpc request via http returned string "+bos.toString());
      return bos.toString();
   }

   private static void debug(String message) {
      if (debugOn)
         System.out.println("debug: "+message);
   }

}
