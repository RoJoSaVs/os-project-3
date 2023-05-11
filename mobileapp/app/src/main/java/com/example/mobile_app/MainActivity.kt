package com.example.mobile_app

import android.app.Activity
import android.media.MediaPlayer
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.absolutePadding
import androidx.compose.foundation.layout.aspectRatio
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.grid.GridCells
import androidx.compose.foundation.lazy.grid.LazyVerticalGrid
import androidx.compose.foundation.shape.CutCornerShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Favorite
import androidx.compose.material.icons.filled.KeyboardArrowDown
import androidx.compose.material.icons.filled.KeyboardArrowUp
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.AlertDialogDefaults.shape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Divider
import androidx.compose.material3.DropdownMenu
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Slider
import androidx.compose.material3.SliderDefaults
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.ExperimentalComposeUiApi
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.drawWithContent
import androidx.compose.ui.geometry.Size
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.RectangleShape
import androidx.compose.ui.layout.onGloballyPositioned
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.LocalDensity
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontFamily
import androidx.compose.ui.text.font.FontStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.text.input.TextFieldValue
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.compose.ui.unit.toSize
import com.example.mobile_app.ui.theme.MobileappTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            MobileappTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
//                    getCode()
                    numPath(1.0f)
                }
            }
        }
    }
}


@Composable
fun numPath(sizeNumPad:Float)
{   var textInputFromPad by remember { mutableStateOf("") }
    val mContext = LocalContext.current

    // Declaring and Initializing
    // the MediaPlayer to play "audio.mp3"
    val mMediaPlayer = MediaPlayer.create(mContext, R.raw.click)
    val mMediaPlayer2 = MediaPlayer.create(mContext, R.raw.click2)
    val level = MediaPlayer.create(mContext, R.raw.level)
    val damage = MediaPlayer.create(mContext, R.raw.damage)

    Box(modifier = Modifier.background(Color.DarkGray)) {
        Column(
            Modifier
                .fillMaxWidth()
                .absolutePadding(0.dp, 70.dp, 0.dp, 0.dp),
            horizontalAlignment = Alignment.CenterHorizontally
        ){
            Text(
                text = "$textInputFromPad",
                color = Color.LightGray,
                fontSize = 50.sp,
                fontFamily = FontFamily.Monospace,
                fontWeight = FontWeight.Bold,
                textAlign = TextAlign.Center,
            )
        }
        Column(modifier = Modifier.absolutePadding(0.dp, 150.dp, 0.dp, 0.dp)) {
            LazyVerticalGrid(
                columns = GridCells.Fixed(3),
                content = {
                    items(10){index ->
                        Button(
                            onClick = {
                                mMediaPlayer.start()
                                textInputFromPad += "$index"},
                            modifier = Modifier
                                .padding((7 * (4 - sizeNumPad)).dp)
                                .size((50 + sizeNumPad * 15).dp),
                            colors = ButtonDefaults.buttonColors(Color.Black),
                        ) {
                            Text("$index", color = Color.LightGray, fontSize = (17 * sizeNumPad).sp)
                        }
                    }
                }
            )
        }
        Row(modifier = Modifier.absolutePadding(10.dp, 650.dp, 10.dp, 0.dp)) {
            // Variables for control
            val openDialog = remember { mutableStateOf(false)  }

            Button(
                onClick = {
                    mMediaPlayer2.start()
                    textInputFromPad = textInputFromPad.dropLast(1)},
                modifier = Modifier
                    .size(80.dp),
                colors = ButtonDefaults.buttonColors(Color.Gray)
            ) {
                Text("X", color = Color.White, fontSize = 25.sp)
            }


            Button(
                onClick = {
                    if(textInputFromPad == "1234"){
                        openDialog.value = true
                        level.start()
                    }
                    else{
                        damage.start()
                    }
                    textInputFromPad = ""
                          },
                modifier = Modifier
                    .padding(start = 200.dp, end = 0.dp)
                    .size(80.dp),
                colors = ButtonDefaults.buttonColors(Color(0xFF003EBA))
            ) {
                Text("✓", color = Color.White, fontSize = 25.sp)
            }

            if (openDialog.value) {
                AlertDialog(
                    onDismissRequest = {
                        // Dismiss the dialog when the user clicks outside the dialog or on the back
                        // button. If you want to disable that functionality, simply use an empty
                        // onCloseRequest.
                        openDialog.value = false
                    },
                    title = {
                        Text(text = "Code ")
                    },
                    text = {
                        Text("The code added were correct")
                    },
                    confirmButton = {
                        Button(
                            onClick = {
                                openDialog.value = false
                                // do something else
                            }) {
                            Text("Done")
                        }
                    }
                )
            }
        }
    }
}






@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun getCode()
{
    var codeUserInputValue by remember { mutableStateOf(TextFieldValue("")) }
    var sliderPosition by remember { mutableStateOf(1f) }

    Column(
        Modifier
            .fillMaxWidth()
            .absolutePadding(0.dp, 100.dp, 0.dp, 0.dp),
        horizontalAlignment = Alignment.CenterHorizontally
    ){
        Text(
            text = "Set attributes",
            color = Color.Blue,
            fontSize = 30.sp,
            fontFamily = FontFamily.Monospace,
            textAlign = TextAlign.Center,
        )
    }

    Column(
        Modifier
            .fillMaxWidth()
            .absolutePadding(10.dp, 200.dp, 10.dp, 0.dp),
        horizontalAlignment = Alignment.CenterHorizontally
    ){
        TextField(
            value = codeUserInputValue,
            label = {Text(text = "Add your code")},
            keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
            onValueChange = {
                if(it.text.length <= 4 ) {
                    codeUserInputValue = it
                }
            }
        )
    }

    Column(
        Modifier
            .fillMaxWidth()
            .absolutePadding(30.dp, 300.dp, 30.dp, 0.dp),
        horizontalAlignment = Alignment.CenterHorizontally
    ){
        Text(
            text = "Select number size",
            color = Color.Blue,
            fontSize = 20.sp,
            fontFamily = FontFamily.Monospace,
            textAlign = TextAlign.Center,
        )


        Text(text = sliderPosition.toString(), style = MaterialTheme.typography.labelLarge)
        Slider(
            value = sliderPosition,
            onValueChange = { sliderPosition = it },
            valueRange = 1f..3f,
            steps = 1,
            colors = SliderDefaults.colors(
                thumbColor = MaterialTheme.colorScheme.secondary,
                activeTrackColor = MaterialTheme.colorScheme.secondary
            )
        )
    }

    Column(
        Modifier
            .fillMaxWidth()
            .absolutePadding(10.dp, 600.dp, 10.dp, 0.dp),
        horizontalAlignment = Alignment.CenterHorizontally
    )
        {
            Button(onClick = { /*TODO*/ },
                colors = ButtonDefaults.buttonColors(Color(0XFF0F9D58)),
                modifier = Modifier
                    .height(60.dp)
                    .width(100.dp)
            ) {
                Text("Done", color = Color.White, fontSize = 20.sp)
            }
        }
}