package com.cryptowrist;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class AddressActivity extends Activity {

	static {
		System.loadLibrary("mainactivitylib");
	}
	
	public native String get_balance(String addr);
	public native String transaction(String sender, String receiver, int amount);
	
	String sender_address;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_address);
		
		Intent intent = getIntent();
		sender_address = intent.getExtras().getString("address");
		
		TextView addr_txt = (TextView) findViewById(R.id.editText1);
		addr_txt.setText(sender_address);
		
		TextView addr_balance = (TextView) findViewById(R.id.textView2);
		addr_balance.setText("Balance: "+get_balance(sender_address));
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.address, menu);
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
	
	public void btnClick(View view){
		EditText receiver = (EditText) findViewById(R.id.editText3);
		EditText amount = (EditText) findViewById(R.id.editText2);
		int amount_val = Integer.parseInt(amount.getText().toString());
		receiver.setText("Details: "+transaction(sender_address, receiver.getText().toString(), amount_val));
	}
}
