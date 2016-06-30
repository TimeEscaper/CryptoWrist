package com.cryptowrist;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;

import java.io.File;

public class ListActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.list_activity);
		

		
		File list_folder = new File("/sdcard/cryptowrist");
		File[] files = list_folder.listFiles();
		String file_list[] = new String[files.length];
		for(int i=0; i<files.length; i++)
			file_list[i] = files[i].getName();
		
		ListView list_view = (ListView) findViewById(R.id.listView1);
		
		//String[] file_list = new String[] {"fdsf", "sdf", "sfsdf"};
		
		ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, file_list);
		
		list_view.setAdapter(adapter);
		
		list_view.setOnItemClickListener(new AdapterView.OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> parent, View itemClicked, int position,
					long id) {
				//Toast.makeText(getApplicationContext(), ((TextView) itemClicked).getText(),
				       // Toast.LENGTH_SHORT).show();
				Intent intent = new Intent(ListActivity.this, AddressActivity.class);
				intent.putExtra("address",((TextView) itemClicked).getText().toString() );
				startActivity(intent);
				
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.list, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
}
